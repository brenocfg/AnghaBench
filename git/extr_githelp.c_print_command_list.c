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
typedef  int uint32_t ;
struct cmdname_help {char* name; int category; int /*<<< orphan*/  help; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mput_char (char,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void print_command_list(const struct cmdname_help *cmds,
			       uint32_t mask, int longest)
{
	int i;

	for (i = 0; cmds[i].name; i++) {
		if (cmds[i].category & mask) {
			size_t len = strlen(cmds[i].name);
			printf("   %s   ", cmds[i].name);
			if (longest > len)
				mput_char(' ', longest - len);
			puts(_(cmds[i].help));
		}
	}
}