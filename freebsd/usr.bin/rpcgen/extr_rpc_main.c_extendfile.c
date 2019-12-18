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

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
extendfile(const char *path, const char *ext)
{
	char *res;
	const char *p;
	const char *file;

	if ((file = strrchr(path, '/')) == NULL)
		file = path;
	else
		file++;
	res = xmalloc(strlen(file) + strlen(ext) + 1);
	p = strrchr(file, '.');
	if (p == NULL) {
		p = file + strlen(file);
	}
	(void) strcpy(res, file);
	(void) strcpy(res + (p - file), ext);
	return (res);
}