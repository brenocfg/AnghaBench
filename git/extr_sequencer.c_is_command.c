#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum todo_command { ____Placeholder_todo_command } todo_command ;
struct TYPE_2__ {char* str; char c; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,char const*,char const**) ; 
 TYPE_1__* todo_command_info ; 

__attribute__((used)) static int is_command(enum todo_command command, const char **bol)
{
	const char *str = todo_command_info[command].str;
	const char nick = todo_command_info[command].c;
	const char *p = *bol + 1;

	return skip_prefix(*bol, str, bol) ||
		((nick && **bol == nick) &&
		 (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || !*p) &&
		 (*bol = p));
}