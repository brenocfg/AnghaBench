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
typedef  scalar_t__ register_t ;

/* Variables and functions */
 scalar_t__ cp0_count_get () ; 
 scalar_t__ uart_readable () ; 

int
keyhit(int seconds)
{
	register_t stoptime;

	stoptime = cp0_count_get() + seconds * 100000000;	/* 100 MHz. */
	do {
		if (uart_readable())
			return (1);
	} while (cp0_count_get() < stoptime);
	return (0);
}