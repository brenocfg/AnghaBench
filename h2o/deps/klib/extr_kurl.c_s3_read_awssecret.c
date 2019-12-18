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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *s3_read_awssecret(const char *fn)
{
	char *p, *secret, buf[128], *path;
	FILE *fp;
	int l;
	if (fn == 0) {
		char *home;
		home = getenv("HOME");
		if (home == 0) return 0;
		l = strlen(home) + 12;
		path = (char*)malloc(strlen(home) + 12);
		strcat(strcpy(path, home), "/.awssecret");
	} else path = (char*)fn;
	fp = fopen(path, "r");
	if (path != fn) free(path);
	if (fp == 0) return 0;
	l = fread(buf, 1, 127, fp);
	fclose(fp);
	buf[l] = 0;
	for (p = buf; *p != 0 && *p != '\n'; ++p);
	if (*p == 0) return 0;
	*p = 0; secret = p + 1;
	for (++p; *p != 0 && *p != '\n'; ++p);
	*p = 0;
	l = p - buf + 1;
	p = (char*)malloc(l);
	memcpy(p, buf, l);
	return p;
}