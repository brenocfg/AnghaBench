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

__attribute__((used)) static inline void handle_pending_interrupts(struct spu_state *csa,
					     struct spu *spu)
{
	/* Save, Step 18:
	 *     Handle any pending interrupts from this SPU
	 *     here.  This is OS or hypervisor specific.  One
	 *     option is to re-enable interrupts to handle any
	 *     pending interrupts, with the interrupt handlers
	 *     recognizing the software Context Switch Pending
	 *     flag, to ensure the SPU execution or MFC command
	 *     queue is not restarted.  TBD.
	 */
}