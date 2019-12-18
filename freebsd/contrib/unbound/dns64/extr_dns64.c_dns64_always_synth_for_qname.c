#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct name_tree_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_qstate {TYPE_2__ qinfo; TYPE_1__* env; } ;
struct dns64_env {int /*<<< orphan*/  ignore_aaaa; } ;
struct TYPE_3__ {scalar_t__* modinfo; } ;

/* Variables and functions */
 int dname_count_labels (int /*<<< orphan*/ ) ; 
 struct name_tree_node* name_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dns64_always_synth_for_qname(struct module_qstate* qstate, int id)
{
	struct dns64_env* dns64_env = (struct dns64_env*)qstate->env->modinfo[id];
	int labs = dname_count_labels(qstate->qinfo.qname);
	struct name_tree_node* node = name_tree_lookup(&dns64_env->ignore_aaaa,
		qstate->qinfo.qname, qstate->qinfo.qname_len, labs,
		qstate->qinfo.qclass);
	return (node != NULL);
}