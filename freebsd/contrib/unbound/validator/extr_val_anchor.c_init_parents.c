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
struct val_anchors {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchors_init_parents_locked (struct val_anchors*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_parents(struct val_anchors* anchors)
{
	lock_basic_lock(&anchors->lock);
	anchors_init_parents_locked(anchors);
	lock_basic_unlock(&anchors->lock);
}