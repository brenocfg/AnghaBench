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
 int /*<<< orphan*/  HBIRD_ESTAR_MODE_ADDR ; 
 unsigned long read_hbreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __us2e_freq_get(void *arg)
{
	unsigned long *estar = arg;

	*estar = read_hbreg(HBIRD_ESTAR_MODE_ADDR);
}