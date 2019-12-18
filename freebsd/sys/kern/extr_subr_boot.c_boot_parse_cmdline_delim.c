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
 int boot_parse_arg (char*) ; 
 char* strsep (char**,char const*) ; 

int
boot_parse_cmdline_delim(char *cmdline, const char *delim)
{
	char *v;
	int howto;

	howto = 0;
	while ((v = strsep(&cmdline, delim)) != NULL) {
		if (*v == '\0')
			continue;
		howto |= boot_parse_arg(v);
	}
	return (howto);
}