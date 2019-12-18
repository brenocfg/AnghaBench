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
struct spu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_switch_pending(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 7:
	 * Restore, Step 5:
	 *     Set a software context switch pending flag.
	 *     Done above in Step 3 - disable_interrupts().
	 */
}