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
 scalar_t__ DO_KBD ; 
 scalar_t__ DO_SIO ; 
 int /*<<< orphan*/  putc (int) ; 
 int /*<<< orphan*/  sio_putc (int) ; 

__attribute__((used)) static int
xputc(int c)
{

	if (DO_KBD)
		putc(c);
	if (DO_SIO)
		sio_putc(c);
	return (c);
}