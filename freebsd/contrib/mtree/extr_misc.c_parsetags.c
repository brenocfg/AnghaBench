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
typedef  int /*<<< orphan*/  slist_t ;

/* Variables and functions */
 int /*<<< orphan*/  addtag (int /*<<< orphan*/ *,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  mtree_err (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

void
parsetags(slist_t *list, char *args)
{
	char	*p, *e;
	int	len;

	if (args == NULL) {
		addtag(list, NULL);
		return;
	}
	while ((p = strsep(&args, ",")) != NULL) {
		if (*p == '\0')
			continue;
		len = strlen(p) + 3;	/* "," + p + ",\0" */
		if ((e = malloc(len)) == NULL)
			mtree_err("memory allocation error");
		snprintf(e, len, ",%s,", p);
		addtag(list, e);
	}
}