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
struct pmap_update_page_arg {int /*<<< orphan*/  pte; int /*<<< orphan*/  va; int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_update_page_action(void *arg)
{
	struct pmap_update_page_arg *p = arg;

	tlb_update(p->pmap, p->va, p->pte);
}