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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prom_putchar (char) ; 

__attribute__((used)) static void prom_console_write(struct console *co, const char *s,
			       unsigned count)
{
	/* Do each character */
	while (count--) {
		if (*s == '\n')
			prom_putchar('\r');
		prom_putchar(*s++);
	}
}