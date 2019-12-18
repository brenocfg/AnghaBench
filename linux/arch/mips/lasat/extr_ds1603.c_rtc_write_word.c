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
 int /*<<< orphan*/  rtc_write_databit (unsigned long) ; 

__attribute__((used)) static void rtc_write_word(unsigned long word)
{
	int i;

	for (i = 0; i <= 31; i++) {
		rtc_write_databit(word & 1L);
		word >>= 1;
	}
}