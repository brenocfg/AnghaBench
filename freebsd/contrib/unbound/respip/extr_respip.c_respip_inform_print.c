#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  txt ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct TYPE_6__ {scalar_t__ ss_family; } ;
struct respip_addr_info {int net; int /*<<< orphan*/  addrlen; TYPE_3__ addr; } ;
struct local_rrset {TYPE_2__* rrset; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; TYPE_3__ addr; } ;
typedef  int /*<<< orphan*/  srcip ;
typedef  int /*<<< orphan*/  respip ;
struct TYPE_4__ {int /*<<< orphan*/ * dname; } ;
struct TYPE_5__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  addr_to_str (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,char*,unsigned int) ; 

void
respip_inform_print(struct respip_addr_info* respip_addr, uint8_t* qname,
	uint16_t qtype, uint16_t qclass, struct local_rrset* local_alias,
	struct comm_reply* repinfo)
{
	char srcip[128], respip[128], txt[512];
	unsigned port;

	if(local_alias)
		qname = local_alias->rrset->rk.dname;
	port = (unsigned)((repinfo->addr.ss_family == AF_INET) ?
		ntohs(((struct sockaddr_in*)&repinfo->addr)->sin_port) :
		ntohs(((struct sockaddr_in6*)&repinfo->addr)->sin6_port));
	addr_to_str(&repinfo->addr, repinfo->addrlen, srcip, sizeof(srcip));
	addr_to_str(&respip_addr->addr, respip_addr->addrlen,
		respip, sizeof(respip));
	snprintf(txt, sizeof(txt), "%s/%d inform %s@%u", respip,
		respip_addr->net, srcip, port);
	log_nametypeclass(0, txt, qname, qtype, qclass);
}