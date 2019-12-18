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
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char *
_default_history_file(void)
{
	struct passwd *p;
	static char *path;
	size_t len;

	if (path)
		return path;

	if ((p = getpwuid(getuid())) == NULL)
		return NULL;

	len = strlen(p->pw_dir) + sizeof("/.history");
	if ((path = malloc(len)) == NULL)
		return NULL;

	(void)snprintf(path, len, "%s/.history", p->pw_dir);
	return path;
}