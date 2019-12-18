#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ _edns_present; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 scalar_t__ ldns_pkt_edns_data (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_edns_do (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_edns_extended_rcode (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_edns_udp_size (TYPE_1__ const*) ; 

bool
ldns_pkt_edns(const ldns_pkt *pkt) {
	return (ldns_pkt_edns_udp_size(pkt) > 0 ||
		ldns_pkt_edns_extended_rcode(pkt) > 0 ||
		ldns_pkt_edns_data(pkt) ||
		ldns_pkt_edns_do(pkt) ||
                pkt->_edns_present
	       );
}