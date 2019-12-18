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
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* savestr (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xalloc (scalar_t__) ; 

__attribute__((used)) static FILE *
tryopen(const char *path, const char *fname)
{
	char *fn;
	FILE *fp;

	if (path == NULL)
		fn = savestr(fname);
	else {
		fn = xalloc(strlen(path) + strlen(fname) + 2);
		sprintf(fn, "%s/%s", path, fname);
	}
	fp = fopen(fn, "r");
	free(fn);
	return (fp);
}