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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static void
cfg_set_bit(uint8_t* bitlist, size_t len, int id)
{
	int pos = id/8;
	log_assert((size_t)pos < len);
	(void)len;
	bitlist[pos] |= 1<<(id%8);
}