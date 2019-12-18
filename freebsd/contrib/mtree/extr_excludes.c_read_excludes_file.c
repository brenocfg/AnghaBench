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
 int FPARSELN_UNESCCOMM ; 
 int FPARSELN_UNESCCONT ; 
 int FPARSELN_UNESCESC ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct exclude*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  excludes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* fparseln (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  link ; 
 struct exclude* malloc (int) ; 
 int /*<<< orphan*/  mtree_err (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

void
read_excludes_file(const char *name)
{
	FILE *fp;
	char *line;
	struct exclude *e;

	fp = fopen(name, "r");
	if (fp == 0)
		err(1, "%s", name);

	while ((line = fparseln(fp, NULL, NULL, NULL,
	    FPARSELN_UNESCCOMM | FPARSELN_UNESCCONT | FPARSELN_UNESCESC))
	    != NULL) {
		if (line[0] == '\0')
			continue;

		if ((e = malloc(sizeof *e)) == NULL)
			mtree_err("memory allocation error");

		e->glob = line;
		if (strchr(e->glob, '/') != NULL)
			e->pathname = 1;
		else
			e->pathname = 0;
		LIST_INSERT_HEAD(&excludes, e, link);
	}
	fclose(fp);
}