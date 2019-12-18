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
struct coh901318_desc {int /*<<< orphan*/  node; } ;
struct coh901318_chan {int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
coh901318_desc_free(struct coh901318_chan *cohc, struct coh901318_desc *cohd)
{
	list_add_tail(&cohd->node, &cohc->free);
}