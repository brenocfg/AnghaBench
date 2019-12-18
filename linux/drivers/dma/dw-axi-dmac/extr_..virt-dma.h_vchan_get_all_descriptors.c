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
struct virt_dma_chan {int /*<<< orphan*/  desc_completed; int /*<<< orphan*/  desc_issued; int /*<<< orphan*/  desc_submitted; int /*<<< orphan*/  desc_allocated; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static inline void vchan_get_all_descriptors(struct virt_dma_chan *vc,
	struct list_head *head)
{
	list_splice_tail_init(&vc->desc_allocated, head);
	list_splice_tail_init(&vc->desc_submitted, head);
	list_splice_tail_init(&vc->desc_issued, head);
	list_splice_tail_init(&vc->desc_completed, head);
}