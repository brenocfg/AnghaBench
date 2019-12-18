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
struct exclude {char* glob; int pathname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct exclude*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  excludes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  link ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ strchr (char*,char) ; 

void
read_excludes_file(const char *name)
{
	FILE *fp;
	char *line, *str;
	struct exclude *e;
	size_t len;

	fp = fopen(name, "r");
	if (fp == NULL)
		err(1, "%s", name);

	while ((line = fgetln(fp, &len)) != NULL) {
		if (line[len - 1] == '\n')
			len--;
		if (len == 0)
			continue;

		str = malloc(len + 1);
		e = malloc(sizeof *e);
		if (str == NULL || e == NULL)
			errx(1, "memory allocation error");
		e->glob = str;
		memcpy(str, line, len);
		str[len] = '\0';
		if (strchr(str, '/'))
			e->pathname = 1;
		else
			e->pathname = 0;
		LIST_INSERT_HEAD(&excludes, e, link);
	}
	fclose(fp);
}