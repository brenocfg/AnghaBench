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
 int ESC_BOL ; 
 int ESC_FON ; 
 int ESC_HYP ; 
 int ESC_NUM ; 
 int escflags ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  outcount ; 
 int /*<<< orphan*/  putchar (unsigned char) ; 

__attribute__((used)) static void
md_char(unsigned char c)
{
	if (c != '\0') {
		putchar(c);
		if (c == '*')
			escflags |= ESC_FON;
		else
			escflags &= ~ESC_FON;
		outcount++;
	}
	if (c != ']')
		escflags &= ~ESC_HYP;
	if (c == ' ' || c == '\t' || c == '>')
		return;
	if (isdigit(c) == 0)
		escflags &= ~ESC_NUM;
	else if (escflags & ESC_BOL)
		escflags |= ESC_NUM;
	escflags &= ~ESC_BOL;
}