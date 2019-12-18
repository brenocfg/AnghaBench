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
struct tlb_pending_info {int /*<<< orphan*/  vaddrs; int /*<<< orphan*/  nr; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_pending (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlb_pending_func(void *info)
{
	struct tlb_pending_info *t = info;

	__flush_tlb_pending(t->ctx, t->nr, t->vaddrs);
}