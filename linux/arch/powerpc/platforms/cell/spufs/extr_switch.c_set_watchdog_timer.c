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

__attribute__((used)) static inline void set_watchdog_timer(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 4:
	 * Restore, Step 25.
	 *    Set a software watchdog timer, which specifies the
	 *    maximum allowable time for a context save sequence.
	 *
	 *    For present, this implementation will not set a global
	 *    watchdog timer, as virtualization & variable system load
	 *    may cause unpredictable execution times.
	 */
}