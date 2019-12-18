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
struct rb_root {int dummy; } ;
struct drbd_interval {int /*<<< orphan*/  rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  augment_callbacks ; 
 int /*<<< orphan*/  rb_erase_augmented (int /*<<< orphan*/ *,struct rb_root*,int /*<<< orphan*/ *) ; 

void
drbd_remove_interval(struct rb_root *root, struct drbd_interval *this)
{
	rb_erase_augmented(&this->rb, root, &augment_callbacks);
}