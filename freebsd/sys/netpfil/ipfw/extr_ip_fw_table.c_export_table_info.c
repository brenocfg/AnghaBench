#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  kidx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  set; int /*<<< orphan*/  subtype; } ;
struct table_config {scalar_t__ locked; int /*<<< orphan*/  astate; struct table_algo* ta; TYPE_1__ no; int /*<<< orphan*/  tablename; int /*<<< orphan*/  limit; int /*<<< orphan*/  vmask; int /*<<< orphan*/  tflags; } ;
struct table_algo {int /*<<< orphan*/  (* dump_tinfo ) (int /*<<< orphan*/ ,struct table_info*,TYPE_3__*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* print_config ) (int /*<<< orphan*/ ,struct table_info*,int /*<<< orphan*/ ,int) ;} ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int count; int size; TYPE_3__ ta_info; int /*<<< orphan*/  algoname; int /*<<< orphan*/  tablename; int /*<<< orphan*/  flags; int /*<<< orphan*/  limit; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  kidx; int /*<<< orphan*/  set; int /*<<< orphan*/  vmask; int /*<<< orphan*/  tflags; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ipfw_obj_tentry ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TATFLAGS_DATA ; 
 int /*<<< orphan*/  IPFW_TGFLAGS_LOCKED ; 
 struct table_info* KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct table_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct table_info*,TYPE_3__*) ; 
 int table_get_count (struct ip_fw_chain*,struct table_config*) ; 

__attribute__((used)) static void
export_table_info(struct ip_fw_chain *ch, struct table_config *tc,
    ipfw_xtable_info *i)
{
	struct table_info *ti;
	struct table_algo *ta;
	
	i->type = tc->no.subtype;
	i->tflags = tc->tflags;
	i->vmask = tc->vmask;
	i->set = tc->no.set;
	i->kidx = tc->no.kidx;
	i->refcnt = tc->no.refcnt;
	i->count = table_get_count(ch, tc);
	i->limit = tc->limit;
	i->flags |= (tc->locked != 0) ? IPFW_TGFLAGS_LOCKED : 0;
	i->size = i->count * sizeof(ipfw_obj_tentry);
	i->size += sizeof(ipfw_obj_header) + sizeof(ipfw_xtable_info);
	strlcpy(i->tablename, tc->tablename, sizeof(i->tablename));
	ti = KIDX_TO_TI(ch, tc->no.kidx);
	ta = tc->ta;
	if (ta->print_config != NULL) {
		/* Use algo function to print table config to string */
		ta->print_config(tc->astate, ti, i->algoname,
		    sizeof(i->algoname));
	} else
		strlcpy(i->algoname, ta->name, sizeof(i->algoname));
	/* Dump algo-specific data, if possible */
	if (ta->dump_tinfo != NULL) {
		ta->dump_tinfo(tc->astate, ti, &i->ta_info);
		i->ta_info.flags |= IPFW_TATFLAGS_DATA;
	}
}