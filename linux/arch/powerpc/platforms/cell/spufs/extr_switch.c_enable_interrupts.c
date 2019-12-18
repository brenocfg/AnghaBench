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
struct spu_state {int dummy; } ;
struct spu {int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS0_INTR_MASK ; 
 unsigned long CLASS1_ENABLE_SEGMENT_FAULT_INTR ; 
 unsigned long CLASS1_ENABLE_STORAGE_FAULT_INTR ; 
 int /*<<< orphan*/  CLASS1_INTR_MASK ; 
 int /*<<< orphan*/  CLASS2_INTR_MASK ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_int_mask_set (struct spu*,int,unsigned long) ; 
 int /*<<< orphan*/  spu_int_stat_clear (struct spu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enable_interrupts(struct spu_state *csa, struct spu *spu)
{
	unsigned long class1_mask = CLASS1_ENABLE_SEGMENT_FAULT_INTR |
	    CLASS1_ENABLE_STORAGE_FAULT_INTR;

	/* Save, Step 49:
	 * Restore, Step 22:
	 *     Reset and then enable interrupts, as
	 *     needed by OS.
	 *
	 *     This implementation enables only class1
	 *     (translation) interrupts.
	 */
	spin_lock_irq(&spu->register_lock);
	spu_int_stat_clear(spu, 0, CLASS0_INTR_MASK);
	spu_int_stat_clear(spu, 1, CLASS1_INTR_MASK);
	spu_int_stat_clear(spu, 2, CLASS2_INTR_MASK);
	spu_int_mask_set(spu, 0, 0ul);
	spu_int_mask_set(spu, 1, class1_mask);
	spu_int_mask_set(spu, 2, 0ul);
	spin_unlock_irq(&spu->register_lock);
}