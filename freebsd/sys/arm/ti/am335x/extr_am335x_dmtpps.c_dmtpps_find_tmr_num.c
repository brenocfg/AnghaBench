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
 int dmtpps_find_tmr_num_by_padconf () ; 
 int dmtpps_find_tmr_num_by_tunable () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
dmtpps_find_tmr_num(void)
{
	int tmr_num;

	if ((tmr_num = dmtpps_find_tmr_num_by_tunable()) == 0)
		tmr_num = dmtpps_find_tmr_num_by_padconf();

	if (tmr_num <= 0) {
		printf("am335x_dmtpps: PPS driver not enabled: unable to find "
		    "or configure a capture input pin\n");
		tmr_num = -1; /* Must return non-zero to prevent re-probing. */
	}
	return (tmr_num);
}