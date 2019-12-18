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
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
printb(int b, const char *str)
{
	int i;
	int gotsome = 0;

	if (b == 0)
		return;
	while ((i = *str++) != 0) {
		if (b & (1 << (i-1))) {
			if (gotsome == 0)
				i = '<';
			else
				i = ',';
			putchar(i);
			gotsome = 1;
			for (; (i = *str) > 32; str++)
				putchar(i);
		} else
			while (*str > 32)
				str++;
	}
	if (gotsome)
		putchar('>');
}