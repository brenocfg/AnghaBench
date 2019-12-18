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
struct debug_buffer {int /*<<< orphan*/  page; struct admhcd* ahcd; } ;
struct admhcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  ed_head; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t show_list (struct admhcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t fill_async_buffer(struct debug_buffer *buf)
{
	struct admhcd		*ahcd;
	size_t			temp;
	unsigned long		flags;

	ahcd = buf->ahcd;

	spin_lock_irqsave(&ahcd->lock, flags);
	temp = show_list(ahcd, buf->page, PAGE_SIZE, ahcd->ed_head);
	spin_unlock_irqrestore(&ahcd->lock, flags);

	return temp;
}