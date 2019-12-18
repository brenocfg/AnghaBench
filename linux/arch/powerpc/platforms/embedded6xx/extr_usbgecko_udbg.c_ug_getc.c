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
 int UG_READ_ATTEMPTS ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  ug_io_base ; 
 int /*<<< orphan*/  ug_is_rxfifo_ready () ; 
 int ug_raw_getc () ; 

__attribute__((used)) static int ug_getc(void)
{
	int count = UG_READ_ATTEMPTS;

	if (!ug_io_base)
		return -1;

	while (!ug_is_rxfifo_ready() && count--)
		barrier();
	return ug_raw_getc();
}