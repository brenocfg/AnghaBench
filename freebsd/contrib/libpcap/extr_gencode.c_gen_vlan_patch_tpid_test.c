#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct slist {int /*<<< orphan*/ * next; } ;
struct block {TYPE_1__* head; } ;
struct TYPE_6__ {int is_vlan_vloffset; int /*<<< orphan*/  off_linktype; int /*<<< orphan*/  off_linkpl; } ;
typedef  TYPE_2__ compiler_state_t ;
struct TYPE_5__ {int /*<<< orphan*/ * stmts; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_vlan_vloffset_add (TYPE_2__*,int /*<<< orphan*/ *,int,struct slist*) ; 
 int /*<<< orphan*/  sappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gen_vlan_patch_tpid_test(compiler_state_t *cstate, struct block *b_tpid)
{
	struct slist s;

	/* offset determined at run time, shift variable part */
	s.next = NULL;
	cstate->is_vlan_vloffset = 1;
	gen_vlan_vloffset_add(cstate, &cstate->off_linkpl, 4, &s);
	gen_vlan_vloffset_add(cstate, &cstate->off_linktype, 4, &s);

	/* we get a pointer to a chain of or-ed blocks, patch first of them */
	sappend(s.next, b_tpid->head->stmts);
	b_tpid->head->stmts = s.next;
}