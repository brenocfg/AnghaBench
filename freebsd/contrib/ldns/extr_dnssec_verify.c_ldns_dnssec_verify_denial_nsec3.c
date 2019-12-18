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
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_pkt_rcode ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dnssec_verify_denial_nsec3_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_verify_denial_nsec3(ldns_rr *rr,
						  ldns_rr_list *nsecs,
						  ldns_rr_list *rrsigs,
						  ldns_pkt_rcode packet_rcode,
						  ldns_rr_type packet_qtype,
						  bool packet_nodata)
{
	return ldns_dnssec_verify_denial_nsec3_match(
				rr, nsecs, rrsigs, packet_rcode,
				packet_qtype, packet_nodata, NULL
	       );
}