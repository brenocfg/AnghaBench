#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dip6; int /*<<< orphan*/  sip6; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_12__ {TYPE_4__ dip; TYPE_2__ sip; } ;
struct TYPE_14__ {TYPE_6__ a6; TYPE_5__ a4; } ;
struct tflow_entry {TYPE_7__ a; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  proto; } ;
struct tentry_info {scalar_t__ subtype; scalar_t__ paddr; } ;
struct fhashentry6 {int /*<<< orphan*/  dip6; int /*<<< orphan*/  sip6; } ;
struct TYPE_10__ {void* s_addr; } ;
struct TYPE_8__ {void* s_addr; } ;
struct fhashentry4 {TYPE_3__ dip; TYPE_1__ sip; } ;
struct fhashentry {scalar_t__ af; void* sport; void* dport; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tei_to_fhash_ent(struct tentry_info *tei, struct fhashentry *ent)
{
#ifdef INET
	struct fhashentry4 *fe4;
#endif
#ifdef INET6
	struct fhashentry6 *fe6;
#endif
	struct tflow_entry *tfe;

	tfe = (struct tflow_entry *)tei->paddr;

	ent->af = tei->subtype;
	ent->proto = tfe->proto;
	ent->dport = ntohs(tfe->dport);
	ent->sport = ntohs(tfe->sport);

	if (tei->subtype == AF_INET) {
#ifdef INET
		fe4 = (struct fhashentry4 *)ent;
		fe4->sip.s_addr = ntohl(tfe->a.a4.sip.s_addr);
		fe4->dip.s_addr = ntohl(tfe->a.a4.dip.s_addr);
#endif
#ifdef INET6
	} else if (tei->subtype == AF_INET6) {
		fe6 = (struct fhashentry6 *)ent;
		fe6->sip6 = tfe->a.a6.sip6;
		fe6->dip6 = tfe->a.a6.dip6;
#endif
	} else {
		/* Unknown CIDR type */
		return (EINVAL);
	}

	return (0);
}