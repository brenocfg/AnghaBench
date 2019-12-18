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
struct tty_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void __serial_clock_off(struct tty_struct *tty)
{
	/* TODO: Some chipset requires to disable UART clock on client
	 * side to save power consumption or manual work is required.
	 * Please put your code to control UART clock off here if needed
	 */
}