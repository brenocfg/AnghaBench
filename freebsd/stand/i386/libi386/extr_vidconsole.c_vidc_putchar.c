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
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  teken ; 
 int /*<<< orphan*/  teken_input (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  vidc_biosputchar (int) ; 

__attribute__((used)) static void
vidc_putchar(int c)
{
	unsigned char ch = c;

	if (buffer != NULL)
		teken_input(&teken, &ch, sizeof (ch));
	else
		vidc_biosputchar(c);
}