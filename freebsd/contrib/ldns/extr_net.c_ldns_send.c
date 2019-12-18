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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MIN_BUFLEN ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_pkt2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_tsig (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (scalar_t__,int) ; 
 int /*<<< orphan*/  ldns_send_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_send(ldns_pkt **result_packet, ldns_resolver *r, const ldns_pkt *query_pkt)
{
	ldns_buffer *qb;
	ldns_status result;
	ldns_rdf *tsig_mac = NULL;

	qb = ldns_buffer_new(LDNS_MIN_BUFLEN);

	if (query_pkt && ldns_pkt_tsig(query_pkt)) {
		tsig_mac = ldns_rr_rdf(ldns_pkt_tsig(query_pkt), 3);
	}

	if (!query_pkt ||
	    ldns_pkt2buffer_wire(qb, query_pkt) != LDNS_STATUS_OK) {
		result = LDNS_STATUS_ERR;
	} else {
        	result = ldns_send_buffer(result_packet, r, qb, tsig_mac);
	}

	ldns_buffer_free(qb);

	return result;
}