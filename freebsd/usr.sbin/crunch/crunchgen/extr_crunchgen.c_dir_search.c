#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* str; struct TYPE_3__* next; } ;
typedef  TYPE_1__ strlst_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  is_dir (char*) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 TYPE_1__* srcdirs ; 
 char* strdup (char*) ; 

char *dir_search(char *progname)
{
	char path[MAXPATHLEN];
	strlst_t *dir;
	char *srcdir;

	for (dir = srcdirs; dir != NULL; dir = dir->next) {
		snprintf(path, MAXPATHLEN, "%s/%s", dir->str, progname);
		if (!is_dir(path))
			continue;

		if ((srcdir = strdup(path)) == NULL)
			out_of_memory();

		return srcdir;
	}
	return NULL;
}