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
struct gtm_timer {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int fls_long (unsigned long) ; 
 int gtm_set_ref_timer16 (struct gtm_timer*,int,unsigned long,int) ; 

int gtm_set_timer16(struct gtm_timer *tmr, unsigned long usec, bool reload)
{
	/* quite obvious, frequency which is enough for µSec precision */
	int freq = 1000000;
	unsigned int bit;

	bit = fls_long(usec);
	if (bit > 15) {
		freq >>= bit - 15;
		usec >>= bit - 15;
	}

	if (!freq)
		return -EINVAL;

	return gtm_set_ref_timer16(tmr, freq, usec, reload);
}