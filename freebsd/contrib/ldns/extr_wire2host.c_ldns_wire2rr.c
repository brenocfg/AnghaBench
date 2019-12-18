#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  scalar_t__ ldns_pkt_section ;

/* Variables and functions */
 scalar_t__ LDNS_SECTION_QUESTION ; 
 int /*<<< orphan*/  LDNS_STATUS_CHECK_GOTO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_STATUS_PACKET_OVERFLOW ; 
 int /*<<< orphan*/  ldns_read_uint16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_read_uint32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new () ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_question (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_wire2dname (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,size_t,size_t*) ; 
 int /*<<< orphan*/  ldns_wire2rdf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t*) ; 
 int /*<<< orphan*/  status_error ; 

ldns_status
ldns_wire2rr(ldns_rr **rr_p, const uint8_t *wire, size_t max,
             size_t *pos, ldns_pkt_section section)
{
	ldns_rdf *owner = NULL;
	ldns_rr *rr = ldns_rr_new();
	ldns_status status;

	status = ldns_wire2dname(&owner, wire, max, pos);
	LDNS_STATUS_CHECK_GOTO(status, status_error);

	ldns_rr_set_owner(rr, owner);

	if (*pos + 4 > max) {
		status = LDNS_STATUS_PACKET_OVERFLOW;
		goto status_error;
	}

	ldns_rr_set_type(rr, ldns_read_uint16(&wire[*pos]));
	*pos = *pos + 2;

	ldns_rr_set_class(rr, ldns_read_uint16(&wire[*pos]));
	*pos = *pos + 2;

	if (section != LDNS_SECTION_QUESTION) {
		if (*pos + 4 > max) {
			status = LDNS_STATUS_PACKET_OVERFLOW;
			goto status_error;
		}
		ldns_rr_set_ttl(rr, ldns_read_uint32(&wire[*pos]));

		*pos = *pos + 4;
		status = ldns_wire2rdf(rr, wire, max, pos);

		LDNS_STATUS_CHECK_GOTO(status, status_error);
        ldns_rr_set_question(rr, false);
	} else {
        ldns_rr_set_question(rr, true);
    }

	*rr_p = rr;
	return LDNS_STATUS_OK;

status_error:
	ldns_rr_free(rr);
	return status;
}