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
typedef  int u_int ;
struct agg_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE (int,int,int) ; 
 int /*<<< orphan*/  WPREG_TIMER_ENABLE ; 
 int /*<<< orphan*/  WPREG_TIMER_FREQ ; 
 int WP_TIMER_FREQ_PRESCALE_SHIFT ; 
 int /*<<< orphan*/  wp_wrreg (struct agg_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wp_settimer(struct agg_info *ess, u_int divide)
{
	u_int prescale = 0;

	RANGE(divide, 2, 32 << 7);

	for (; divide > 32; divide >>= 1) {
		prescale++;
		divide++;
	}

	for (; prescale < 7 && divide > 2 && !(divide & 1); divide >>= 1)
		prescale++;

	wp_wrreg(ess, WPREG_TIMER_ENABLE, 0);
	wp_wrreg(ess, WPREG_TIMER_FREQ, 0x9000 |
	    (prescale << WP_TIMER_FREQ_PRESCALE_SHIFT) | (divide - 1));
	wp_wrreg(ess, WPREG_TIMER_ENABLE, 1);
}