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
typedef  int /*<<< orphan*/  abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  add_mapping (struct string_list*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (char) ; 
 char* parse_name_and_email (char*,char**,char**,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void read_mailmap_line(struct string_list *map, char *buffer,
			      char **repo_abbrev)
{
	char *name1 = NULL, *email1 = NULL, *name2 = NULL, *email2 = NULL;
	if (buffer[0] == '#') {
		static const char abbrev[] = "# repo-abbrev:";
		int abblen = sizeof(abbrev) - 1;
		int len = strlen(buffer);

		if (!repo_abbrev)
			return;

		if (len && buffer[len - 1] == '\n')
			buffer[--len] = 0;
		if (!strncmp(buffer, abbrev, abblen)) {
			char *cp;

			free(*repo_abbrev);

			for (cp = buffer + abblen; isspace(*cp); cp++)
				; /* nothing */
			*repo_abbrev = xstrdup(cp);
		}
		return;
	}
	if ((name2 = parse_name_and_email(buffer, &name1, &email1, 0)) != NULL)
		parse_name_and_email(name2, &name2, &email2, 1);

	if (email1)
		add_mapping(map, name1, email1, name2, email2);
}