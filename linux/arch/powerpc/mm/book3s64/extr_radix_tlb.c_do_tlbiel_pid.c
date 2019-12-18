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
struct tlbiel_pid {scalar_t__ ric; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ RIC_FLUSH_ALL ; 
 scalar_t__ RIC_FLUSH_PWC ; 
 scalar_t__ RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  _tlbiel_pid (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void do_tlbiel_pid(void *info)
{
	struct tlbiel_pid *t = info;

	if (t->ric == RIC_FLUSH_TLB)
		_tlbiel_pid(t->pid, RIC_FLUSH_TLB);
	else if (t->ric == RIC_FLUSH_PWC)
		_tlbiel_pid(t->pid, RIC_FLUSH_PWC);
	else
		_tlbiel_pid(t->pid, RIC_FLUSH_ALL);
}