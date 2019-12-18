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
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_mailmap_line (struct string_list*,char*,char**) ; 
 char* strchrnul (char*,char) ; 

__attribute__((used)) static void read_mailmap_string(struct string_list *map, char *buf,
				char **repo_abbrev)
{
	while (*buf) {
		char *end = strchrnul(buf, '\n');

		if (*end)
			*end++ = '\0';

		read_mailmap_line(map, buf, repo_abbrev);
		buf = end;
	}
}