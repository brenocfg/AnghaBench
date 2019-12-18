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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  txt ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname; } ;
struct local_zone {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  addr_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 char* local_zone_type2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,unsigned int) ; 

__attribute__((used)) static void
lz_inform_print(struct local_zone* z, struct query_info* qinfo,
	struct comm_reply* repinfo)
{
	char ip[128], txt[512];
	char zname[LDNS_MAX_DOMAINLEN+1];
	uint16_t port = ntohs(((struct sockaddr_in*)&repinfo->addr)->sin_port);
	dname_str(z->name, zname);
	addr_to_str(&repinfo->addr, repinfo->addrlen, ip, sizeof(ip));
	snprintf(txt, sizeof(txt), "%s %s %s@%u", zname, local_zone_type2str(z->type), ip,
		(unsigned)port);
	log_nametypeclass(0, txt, qinfo->qname, qinfo->qtype, qinfo->qclass);
}