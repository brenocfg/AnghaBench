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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_wire_canonical (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 

ldns_status
ldns_rrsig2buffer_wire(ldns_buffer *buffer, const ldns_rr *rr)
{
	uint16_t i;

	/* it must be a sig RR */
	if (ldns_rr_get_type(rr) != LDNS_RR_TYPE_RRSIG) {
		return LDNS_STATUS_ERR;
	}
	
	/* Convert all the rdfs, except the actual signature data
	 * rdf number 8  - the last, hence: -1 */
	for (i = 0; i < ldns_rr_rd_count(rr) - 1; i++) {
		(void) ldns_rdf2buffer_wire_canonical(buffer, 
				ldns_rr_rdf(rr, i));
	}

	return ldns_buffer_status(buffer);
}