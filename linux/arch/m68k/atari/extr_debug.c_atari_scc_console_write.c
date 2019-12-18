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
 int /*<<< orphan*/  ata_scc_out (char) ; 

__attribute__((used)) static void atari_scc_console_write(struct console *co, const char *str,
				    unsigned int count)
{
	while (count--) {
		if (*str == '\n')
			ata_scc_out('\r');
		ata_scc_out(*str++);
	}
}