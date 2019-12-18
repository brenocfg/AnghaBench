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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int error_errno (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  read_mailmap_line (struct string_list*,char*,char**) ; 

__attribute__((used)) static int read_mailmap_file(struct string_list *map, const char *filename,
			     char **repo_abbrev)
{
	char buffer[1024];
	FILE *f;

	if (!filename)
		return 0;

	f = fopen(filename, "r");
	if (!f) {
		if (errno == ENOENT)
			return 0;
		return error_errno("unable to open mailmap at %s", filename);
	}

	while (fgets(buffer, sizeof(buffer), f) != NULL)
		read_mailmap_line(map, buffer, repo_abbrev);
	fclose(f);
	return 0;
}