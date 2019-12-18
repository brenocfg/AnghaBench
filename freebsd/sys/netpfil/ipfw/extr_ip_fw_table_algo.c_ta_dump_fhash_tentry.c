#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  dip6; int /*<<< orphan*/  sip6; } ;
struct TYPE_17__ {void* s_addr; } ;
struct TYPE_15__ {void* s_addr; } ;
struct TYPE_18__ {TYPE_5__ dip; TYPE_3__ sip; } ;
struct TYPE_21__ {TYPE_8__ a6; TYPE_6__ a4; } ;
struct tflow_entry {scalar_t__ af; TYPE_9__ a; void* sport; void* dport; int /*<<< orphan*/  proto; } ;
struct table_info {int dummy; } ;
struct fhashentry6 {int /*<<< orphan*/  dip6; int /*<<< orphan*/  sip6; } ;
struct TYPE_19__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  s_addr; } ;
struct fhashentry4 {TYPE_7__ dip; TYPE_4__ sip; } ;
struct fhashentry {scalar_t__ af; int /*<<< orphan*/  value; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  proto; } ;
struct fhash_cfg {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_13__ {struct tflow_entry flow; } ;
struct TYPE_12__ {scalar_t__ subtype; int masklen; TYPE_2__ v; TYPE_1__ k; } ;
typedef  TYPE_10__ ipfw_obj_tentry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ta_dump_fhash_tentry(void *ta_state, struct table_info *ti, void *e,
    ipfw_obj_tentry *tent)
{
	struct fhash_cfg *cfg;
	struct fhashentry *ent;
	struct fhashentry4 *fe4;
#ifdef INET6
	struct fhashentry6 *fe6;
#endif
	struct tflow_entry *tfe;

	cfg = (struct fhash_cfg *)ta_state;
	ent = (struct fhashentry *)e;
	tfe = &tent->k.flow;

	tfe->af = ent->af;
	tfe->proto = ent->proto;
	tfe->dport = htons(ent->dport);
	tfe->sport = htons(ent->sport);
	tent->v.kidx = ent->value;
	tent->subtype = ent->af;

	if (ent->af == AF_INET) {
		fe4 = (struct fhashentry4 *)ent;
		tfe->a.a4.sip.s_addr = htonl(fe4->sip.s_addr);
		tfe->a.a4.dip.s_addr = htonl(fe4->dip.s_addr);
		tent->masklen = 32;
#ifdef INET6
	} else {
		fe6 = (struct fhashentry6 *)ent;
		tfe->a.a6.sip6 = fe6->sip6;
		tfe->a.a6.dip6 = fe6->dip6;
		tent->masklen = 128;
#endif
	}

	return (0);
}