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
 int fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * terminal_outfile ; 

__attribute__((used)) static int
terminal_putc(int c)
{
	if (terminal_outfile == NULL)
		return -1;
	return fputc(c, terminal_outfile);
}