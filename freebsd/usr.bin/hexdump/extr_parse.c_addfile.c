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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  add (unsigned char*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int getchar () ; 
 scalar_t__ isspace (unsigned char) ; 
 unsigned char* strchr (char*,char) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
addfile(const char *name)
{
	unsigned char *p;
	FILE *fp;
	int ch;
	char buf[2048 + 1];

	if ((fp = fopen(name, "r")) == NULL)
		err(1, "%s", name);
	while (fgets(buf, sizeof(buf), fp)) {
		if (!(p = strchr(buf, '\n'))) {
			warnx("line too long");
			while ((ch = getchar()) != '\n' && ch != EOF);
			continue;
		}
		*p = '\0';
		for (p = buf; *p && isspace(*p); ++p);
		if (!*p || *p == '#')
			continue;
		add(p);
	}
	(void)fclose(fp);
}