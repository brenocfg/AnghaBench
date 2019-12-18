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
struct tlbiel_va {scalar_t__ ric; int /*<<< orphan*/  psize; int /*<<< orphan*/  pid; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 scalar_t__ RIC_FLUSH_ALL ; 
 scalar_t__ RIC_FLUSH_PWC ; 
 scalar_t__ RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  _tlbiel_va (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void do_tlbiel_va(void *info)
{
	struct tlbiel_va *t = info;

	if (t->ric == RIC_FLUSH_TLB)
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_TLB);
	else if (t->ric == RIC_FLUSH_PWC)
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_PWC);
	else
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_ALL);
}