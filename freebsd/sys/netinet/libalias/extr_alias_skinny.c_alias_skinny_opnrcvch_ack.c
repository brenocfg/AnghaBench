#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  void* u_int32_t ;
struct tcphdr {int th_x2; scalar_t__ th_sum; } ;
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_src; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct alias_link {int dummy; } ;
struct OpenReceiveChannelAck {void* port; void* ipAddr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
typedef  int /*<<< orphan*/  ConvDirection ;

/* Variables and functions */
 struct alias_link* FindUdpTcpOut (struct libalias*,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ GetAliasAddress (struct alias_link*) ; 
 int /*<<< orphan*/  GetAliasPort (struct alias_link*) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alias_skinny_opnrcvch_ack(struct libalias *la, struct OpenReceiveChannelAck *opnrcvch_ack,
    struct ip *pip, struct tcphdr *tc,
    struct alias_link *lnk, u_int32_t * localIpAddr,
    ConvDirection direction)
{
	struct in_addr null_addr;
	struct alias_link *opnrcv_lnk;
	u_int32_t localPort;

	(void)lnk;
	(void)direction;

	*localIpAddr = (u_int32_t) opnrcvch_ack->ipAddr;
	localPort = opnrcvch_ack->port;

	null_addr.s_addr = INADDR_ANY;
	opnrcv_lnk = FindUdpTcpOut(la, pip->ip_src, null_addr,
	    htons((u_short) opnrcvch_ack->port), 0,
	    IPPROTO_UDP, 1);
	opnrcvch_ack->ipAddr = (u_int32_t) GetAliasAddress(opnrcv_lnk).s_addr;
	opnrcvch_ack->port = (u_int32_t) ntohs(GetAliasPort(opnrcv_lnk));

	tc->th_sum = 0;
#ifdef _KERNEL
	tc->th_x2 = 1;
#else
	tc->th_sum = TcpChecksum(pip);
#endif
	return (0);
}