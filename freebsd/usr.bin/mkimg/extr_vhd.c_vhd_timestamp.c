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
typedef  int uint32_t ;
typedef  int time_t ;

/* Variables and functions */
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_testing ; 

__attribute__((used)) static uint32_t
vhd_timestamp(void)
{
	time_t t;

	if (!unit_testing) {
		t = time(NULL);
		return (t - 0x386d4380);
	}

	return (0x01234567);
}