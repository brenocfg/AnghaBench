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
struct kafs_data {char* (* get_realm ) (struct kafs_data*,char*) ;} ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_ARLA_CELLSERVDB ; 
 int /*<<< orphan*/  _PATH_ARLA_DEBIAN_CELLSERVDB ; 
 int /*<<< orphan*/  _PATH_CELLSERVDB ; 
 int /*<<< orphan*/  _PATH_OPENAFS_DEBIAN_CELLSERVDB ; 
 int /*<<< orphan*/  _PATH_OPENAFS_MACOSX_CELLSERVDB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 int strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 
 char* stub1 (struct kafs_data*,char*) ; 

__attribute__((used)) static int
file_find_cell(struct kafs_data *data,
	       const char *cell, char **realm, int exact)
{
    FILE *F;
    char buf[1024];
    char *p;
    int ret = -1;

    if ((F = fopen(_PATH_CELLSERVDB, "r"))
	|| (F = fopen(_PATH_ARLA_CELLSERVDB, "r"))
	|| (F = fopen(_PATH_OPENAFS_DEBIAN_CELLSERVDB, "r"))
	|| (F = fopen(_PATH_OPENAFS_MACOSX_CELLSERVDB, "r"))
	|| (F = fopen(_PATH_ARLA_DEBIAN_CELLSERVDB, "r"))) {
	while (fgets(buf, sizeof(buf), F)) {
	    int cmp;

	    if (buf[0] != '>')
		continue; /* Not a cell name line, try next line */
	    p = buf;
	    strsep(&p, " \t\n#");

	    if (exact)
		cmp = strcmp(buf + 1, cell);
	    else
		cmp = strncmp(buf + 1, cell, strlen(cell));

	    if (cmp == 0) {
		/*
		 * We found the cell name we're looking for.
		 * Read next line on the form ip-address '#' hostname
		 */
		if (fgets(buf, sizeof(buf), F) == NULL)
		    break;	/* Read failed, give up */
		p = strchr(buf, '#');
		if (p == NULL)
		    break;	/* No '#', give up */
		p++;
		if (buf[strlen(buf) - 1] == '\n')
		    buf[strlen(buf) - 1] = '\0';
		*realm = (*data->get_realm)(data, p);
		if (*realm && **realm != '\0')
		    ret = 0;
		break;		/* Won't try any more */
	    }
	}
	fclose(F);
    }
    return ret;
}