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
 int IO_KEYBOARD ; 
 int IO_SERIAL ; 
 int ioctrl ; 
 int /*<<< orphan*/  putc (int) ; 
 int /*<<< orphan*/  sio_putc (int) ; 

void
xputc(int c)
{

	if (ioctrl & IO_KEYBOARD)
		putc(c);
	if (ioctrl & IO_SERIAL)
		sio_putc(c);
}