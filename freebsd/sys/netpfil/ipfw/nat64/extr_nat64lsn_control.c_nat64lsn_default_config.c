#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int jmaxlen; scalar_t__ nh_delete_delay; scalar_t__ pg_delete_delay; scalar_t__ st_syn_ttl; scalar_t__ st_close_ttl; scalar_t__ st_estab_ttl; scalar_t__ st_udp_ttl; scalar_t__ st_icmp_ttl; int states_chunks; } ;
typedef  TYPE_1__ ipfw_nat64lsn_cfg ;

/* Variables and functions */
 scalar_t__ NAT64LSN_HOST_AGE ; 
 scalar_t__ NAT64LSN_ICMP_AGE ; 
 int NAT64LSN_JMAXLEN ; 
 scalar_t__ NAT64LSN_PG_AGE ; 
 scalar_t__ NAT64LSN_TCP_EST_AGE ; 
 scalar_t__ NAT64LSN_TCP_FIN_AGE ; 
 scalar_t__ NAT64LSN_TCP_SYN_AGE ; 
 scalar_t__ NAT64LSN_UDP_AGE ; 
 int fls (int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 

__attribute__((used)) static void
nat64lsn_default_config(ipfw_nat64lsn_cfg *uc)
{

	if (uc->jmaxlen == 0)
		uc->jmaxlen = NAT64LSN_JMAXLEN;
	if (uc->jmaxlen > 65536)
		uc->jmaxlen = 65536;
	if (uc->nh_delete_delay == 0)
		uc->nh_delete_delay = NAT64LSN_HOST_AGE;
	if (uc->pg_delete_delay == 0)
		uc->pg_delete_delay = NAT64LSN_PG_AGE;
	if (uc->st_syn_ttl == 0)
		uc->st_syn_ttl = NAT64LSN_TCP_SYN_AGE;
	if (uc->st_close_ttl == 0)
		uc->st_close_ttl = NAT64LSN_TCP_FIN_AGE;
	if (uc->st_estab_ttl == 0)
		uc->st_estab_ttl = NAT64LSN_TCP_EST_AGE;
	if (uc->st_udp_ttl == 0)
		uc->st_udp_ttl = NAT64LSN_UDP_AGE;
	if (uc->st_icmp_ttl == 0)
		uc->st_icmp_ttl = NAT64LSN_ICMP_AGE;

	if (uc->states_chunks == 0)
		uc->states_chunks = 1;
	else if (uc->states_chunks >= 128)
		uc->states_chunks = 128;
	else if (!powerof2(uc->states_chunks))
		uc->states_chunks = 1 << fls(uc->states_chunks);
}