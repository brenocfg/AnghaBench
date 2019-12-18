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
struct tlbiel_va_range {int /*<<< orphan*/  also_pwc; int /*<<< orphan*/  psize; int /*<<< orphan*/  page_size; int /*<<< orphan*/  pid; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tlbiel_va_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_tlbiel_va_range(void *info)
{
	struct tlbiel_va_range *t = info;

	_tlbiel_va_range(t->start, t->end, t->pid, t->page_size,
				    t->psize, t->also_pwc);
}