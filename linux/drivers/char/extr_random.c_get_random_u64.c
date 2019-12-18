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
typedef  scalar_t__ u64 ;
struct batched_entropy {int position; int /*<<< orphan*/  batch_lock; scalar_t__* entropy_u64; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ arch_get_random_long (unsigned long*) ; 
 int /*<<< orphan*/  batched_entropy_u64 ; 
 int /*<<< orphan*/  extract_crng (int /*<<< orphan*/ *) ; 
 struct batched_entropy* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  warn_unseeded_randomness (void**) ; 

u64 get_random_u64(void)
{
	u64 ret;
	unsigned long flags;
	struct batched_entropy *batch;
	static void *previous;

#if BITS_PER_LONG == 64
	if (arch_get_random_long((unsigned long *)&ret))
		return ret;
#else
	if (arch_get_random_long((unsigned long *)&ret) &&
	    arch_get_random_long((unsigned long *)&ret + 1))
	    return ret;
#endif

	warn_unseeded_randomness(&previous);

	batch = raw_cpu_ptr(&batched_entropy_u64);
	spin_lock_irqsave(&batch->batch_lock, flags);
	if (batch->position % ARRAY_SIZE(batch->entropy_u64) == 0) {
		extract_crng((u8 *)batch->entropy_u64);
		batch->position = 0;
	}
	ret = batch->entropy_u64[batch->position++];
	spin_unlock_irqrestore(&batch->batch_lock, flags);
	return ret;
}