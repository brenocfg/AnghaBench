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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct batched_entropy {int position; int /*<<< orphan*/  batch_lock; int /*<<< orphan*/ * entropy_u32; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ arch_get_random_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batched_entropy_u32 ; 
 int /*<<< orphan*/  extract_crng (int /*<<< orphan*/ *) ; 
 struct batched_entropy* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  warn_unseeded_randomness (void**) ; 

u32 get_random_u32(void)
{
	u32 ret;
	unsigned long flags;
	struct batched_entropy *batch;
	static void *previous;

	if (arch_get_random_int(&ret))
		return ret;

	warn_unseeded_randomness(&previous);

	batch = raw_cpu_ptr(&batched_entropy_u32);
	spin_lock_irqsave(&batch->batch_lock, flags);
	if (batch->position % ARRAY_SIZE(batch->entropy_u32) == 0) {
		extract_crng((u8 *)batch->entropy_u32);
		batch->position = 0;
	}
	ret = batch->entropy_u32[batch->position++];
	spin_unlock_irqrestore(&batch->batch_lock, flags);
	return ret;
}