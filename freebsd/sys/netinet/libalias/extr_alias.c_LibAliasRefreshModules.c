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
 int /*<<< orphan*/  LibAliasLoadModule (char*) ; 
 int /*<<< orphan*/  LibAliasUnLoadAllModule () ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int strlen (char*) ; 

int
LibAliasRefreshModules(void)
{
	char buf[256], conf[] = "/etc/libalias.conf";
	FILE *fd;
	int i, len;

	fd = fopen(conf, "r");
	if (fd == NULL)
		err(1, "fopen(%s)", conf);

	LibAliasUnLoadAllModule();

	for (;;) {
		fgets(buf, 256, fd);
		if (feof(fd)) 
		        break;
		len = strlen(buf);
		if (len > 1) {
			for (i = 0; i < len; i++)
				if (!isspace(buf[i]))
					break;
			if (buf[i] == '#')
				continue;
			buf[len - 1] = '\0';
			LibAliasLoadModule(buf);
		}
	}
	fclose(fd);
	return (0);
}