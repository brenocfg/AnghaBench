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
 int /*<<< orphan*/  malta_lcd_putc (int,char) ; 

__attribute__((used)) static void
malta_lcd_print(char *str)
{
	int i;
	
	if (str == NULL)
		return;

	for (i = 0; *str != '\0'; i++, str++)
		malta_lcd_putc(i, *str);
}