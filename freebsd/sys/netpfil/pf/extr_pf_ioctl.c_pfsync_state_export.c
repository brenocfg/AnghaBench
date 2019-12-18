#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pfsync_state {scalar_t__ expire; int /*<<< orphan*/ * bytes; int /*<<< orphan*/ * packets; void* nat_rule; void* anchor; void* rule; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; int /*<<< orphan*/  sync_flags; int /*<<< orphan*/  state_flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  log; int /*<<< orphan*/  direction; void* creation; int /*<<< orphan*/  rt_addr; int /*<<< orphan*/  ifname; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; TYPE_7__* key; } ;
struct TYPE_15__ {TYPE_5__* ptr; } ;
struct TYPE_13__ {TYPE_3__* ptr; } ;
struct TYPE_11__ {TYPE_1__* ptr; } ;
struct pf_state {scalar_t__ creation; int /*<<< orphan*/ * bytes; int /*<<< orphan*/ * packets; TYPE_6__ nat_rule; TYPE_4__ anchor; TYPE_2__ rule; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; scalar_t__ nat_src_node; scalar_t__ src_node; int /*<<< orphan*/  state_flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  log; int /*<<< orphan*/  direction; int /*<<< orphan*/  rt_addr; TYPE_9__* kif; TYPE_8__** key; } ;
struct TYPE_18__ {int /*<<< orphan*/  pfik_name; } ;
struct TYPE_17__ {int /*<<< orphan*/  af; int /*<<< orphan*/  proto; int /*<<< orphan*/ * port; int /*<<< orphan*/ * addr; } ;
struct TYPE_16__ {int /*<<< orphan*/ * port; int /*<<< orphan*/ * addr; } ;
struct TYPE_14__ {int nr; } ;
struct TYPE_12__ {int nr; } ;
struct TYPE_10__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFSYNC_FLAG_NATSRCNODE ; 
 int /*<<< orphan*/  PFSYNC_FLAG_SRCNODE ; 
 size_t PF_SK_STACK ; 
 size_t PF_SK_WIRE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct pfsync_state*,int) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  pf_state_counter_hton (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pf_state_expires (struct pf_state*) ; 
 int /*<<< orphan*/  pf_state_peer_hton (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_uptime ; 

void
pfsync_state_export(struct pfsync_state *sp, struct pf_state *st)
{
	bzero(sp, sizeof(struct pfsync_state));

	/* copy from state key */
	sp->key[PF_SK_WIRE].addr[0] = st->key[PF_SK_WIRE]->addr[0];
	sp->key[PF_SK_WIRE].addr[1] = st->key[PF_SK_WIRE]->addr[1];
	sp->key[PF_SK_WIRE].port[0] = st->key[PF_SK_WIRE]->port[0];
	sp->key[PF_SK_WIRE].port[1] = st->key[PF_SK_WIRE]->port[1];
	sp->key[PF_SK_STACK].addr[0] = st->key[PF_SK_STACK]->addr[0];
	sp->key[PF_SK_STACK].addr[1] = st->key[PF_SK_STACK]->addr[1];
	sp->key[PF_SK_STACK].port[0] = st->key[PF_SK_STACK]->port[0];
	sp->key[PF_SK_STACK].port[1] = st->key[PF_SK_STACK]->port[1];
	sp->proto = st->key[PF_SK_WIRE]->proto;
	sp->af = st->key[PF_SK_WIRE]->af;

	/* copy from state */
	strlcpy(sp->ifname, st->kif->pfik_name, sizeof(sp->ifname));
	bcopy(&st->rt_addr, &sp->rt_addr, sizeof(sp->rt_addr));
	sp->creation = htonl(time_uptime - st->creation);
	sp->expire = pf_state_expires(st);
	if (sp->expire <= time_uptime)
		sp->expire = htonl(0);
	else
		sp->expire = htonl(sp->expire - time_uptime);

	sp->direction = st->direction;
	sp->log = st->log;
	sp->timeout = st->timeout;
	sp->state_flags = st->state_flags;
	if (st->src_node)
		sp->sync_flags |= PFSYNC_FLAG_SRCNODE;
	if (st->nat_src_node)
		sp->sync_flags |= PFSYNC_FLAG_NATSRCNODE;

	sp->id = st->id;
	sp->creatorid = st->creatorid;
	pf_state_peer_hton(&st->src, &sp->src);
	pf_state_peer_hton(&st->dst, &sp->dst);

	if (st->rule.ptr == NULL)
		sp->rule = htonl(-1);
	else
		sp->rule = htonl(st->rule.ptr->nr);
	if (st->anchor.ptr == NULL)
		sp->anchor = htonl(-1);
	else
		sp->anchor = htonl(st->anchor.ptr->nr);
	if (st->nat_rule.ptr == NULL)
		sp->nat_rule = htonl(-1);
	else
		sp->nat_rule = htonl(st->nat_rule.ptr->nr);

	pf_state_counter_hton(st->packets[0], sp->packets[0]);
	pf_state_counter_hton(st->packets[1], sp->packets[1]);
	pf_state_counter_hton(st->bytes[0], sp->bytes[0]);
	pf_state_counter_hton(st->bytes[1], sp->bytes[1]);

}