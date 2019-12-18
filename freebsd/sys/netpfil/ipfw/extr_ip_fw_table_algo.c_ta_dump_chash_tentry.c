#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_9__ {int a4; int /*<<< orphan*/  a6; } ;
struct chashentry {scalar_t__ type; int /*<<< orphan*/  value; TYPE_3__ a; } ;
struct chash_cfg {int mask4; int mask6; } ;
struct TYPE_10__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr6; TYPE_1__ addr; } ;
struct TYPE_11__ {int masklen; TYPE_4__ v; scalar_t__ subtype; TYPE_2__ k; } ;
typedef  TYPE_5__ ipfw_obj_tentry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ta_dump_chash_tentry(void *ta_state, struct table_info *ti, void *e,
    ipfw_obj_tentry *tent)
{
	struct chash_cfg *cfg;
	struct chashentry *ent;

	cfg = (struct chash_cfg *)ta_state;
	ent = (struct chashentry *)e;

	if (ent->type == AF_INET) {
		tent->k.addr.s_addr = htonl(ent->a.a4 << (32 - cfg->mask4));
		tent->masklen = cfg->mask4;
		tent->subtype = AF_INET;
		tent->v.kidx = ent->value;
#ifdef INET6
	} else {
		memcpy(&tent->k.addr6, &ent->a.a6, sizeof(struct in6_addr));
		tent->masklen = cfg->mask6;
		tent->subtype = AF_INET6;
		tent->v.kidx = ent->value;
#endif
	}

	return (0);
}