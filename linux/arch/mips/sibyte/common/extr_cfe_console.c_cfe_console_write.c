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
 int /*<<< orphan*/  cfe_cons_handle ; 
 int cfe_write (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static void cfe_console_write(struct console *cons, const char *str,
		       unsigned int count)
{
	int i, last, written;

	for (i=0, last=0; i<count; i++) {
		if (!str[i])
			/* XXXKW can/should this ever happen? */
			return;
		if (str[i] == '\n') {
			do {
				written = cfe_write(cfe_cons_handle, &str[last], i-last);
				if (written < 0)
					;
				last += written;
			} while (last < i);
			while (cfe_write(cfe_cons_handle, "\r", 1) <= 0)
				;
		}
	}
	if (last != count) {
		do {
			written = cfe_write(cfe_cons_handle, &str[last], count-last);
			if (written < 0)
				;
			last += written;
		} while (last < count);
	}

}