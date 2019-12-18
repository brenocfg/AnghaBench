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
 int /*<<< orphan*/  isascii (unsigned char) ; 
 scalar_t__ isprint (unsigned char) ; 
 int /*<<< orphan*/  putchar (char) ; 
 unsigned char toascii (unsigned char) ; 

__attribute__((used)) static void
vputc(unsigned char ch)
{
	int meta;

	if (!isprint(ch) && !isascii(ch)) {
		(void)putchar('M');
		(void)putchar('-');
		ch = toascii(ch);
		meta = 1;
	} else
		meta = 0;
	if (isprint(ch) || (!meta && (ch == ' ' || ch == '\t' || ch == '\n')))
		(void)putchar(ch);
	else {
		(void)putchar('^');
		(void)putchar(ch == '\177' ? '?' : ch | 0100);
	}
}