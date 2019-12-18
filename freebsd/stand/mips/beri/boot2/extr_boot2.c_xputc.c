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
 int /*<<< orphan*/  beri_putc (int) ; 
 int ioctrl ; 
 int /*<<< orphan*/  sio_putc (int) ; 

__attribute__((used)) static int
xputc(int c)
{
    if (ioctrl & IO_KEYBOARD)
	beri_putc(c);
#if 0
    if (ioctrl & IO_SERIAL)
	sio_putc(c);
#endif
    return c;
}