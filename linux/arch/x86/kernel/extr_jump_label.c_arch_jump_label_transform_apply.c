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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_mutex ; 
 int /*<<< orphan*/  text_poke_bp_batch (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tp_vec ; 
 scalar_t__ tp_vec_nr ; 

void arch_jump_label_transform_apply(void)
{
	if (!tp_vec_nr)
		return;

	mutex_lock(&text_mutex);
	text_poke_bp_batch(tp_vec, tp_vec_nr);
	mutex_unlock(&text_mutex);

	tp_vec_nr = 0;
}