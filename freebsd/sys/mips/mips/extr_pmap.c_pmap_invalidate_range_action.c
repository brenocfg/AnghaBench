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
struct pmap_invalidate_range_arg {int /*<<< orphan*/  eva; int /*<<< orphan*/  sva; int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_invalidate_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_invalidate_range_action(void *arg)
{
	struct pmap_invalidate_range_arg *p = arg;

	tlb_invalidate_range(p->pmap, p->sva, p->eva);
}