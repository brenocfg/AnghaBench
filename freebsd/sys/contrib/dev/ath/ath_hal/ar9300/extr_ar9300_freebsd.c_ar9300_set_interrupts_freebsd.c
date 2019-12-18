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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  ar9300_set_interrupts (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_INT
ar9300_set_interrupts_freebsd(struct ath_hal *ah, HAL_INT ints)
{

	/* nortc = 0 */
	return ar9300_set_interrupts(ah, ints, 0);
}