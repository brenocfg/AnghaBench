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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  push_excludes (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strndup (char*,size_t) ; 

void
read_excludes_file(char *file)
{
	FILE *fp;
	char *buf, *pattern;
	size_t len;

	if (strcmp(file, "-") == 0)
		fp = stdin;
	else if ((fp = fopen(file, "r")) == NULL)
		err(2, "%s", file);
	while ((buf = fgetln(fp, &len)) != NULL) {
		if (buf[len - 1] == '\n')
			len--;
		if ((pattern = strndup(buf, len)) == NULL)
			err(2, "xstrndup");
		push_excludes(pattern);
	}
	if (strcmp(file, "-") != 0)
		fclose(fp);
}