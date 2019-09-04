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
 int /*<<< orphan*/  assert (char const*) ; 
 char* getenv (char*) ; 
 char* mkpathdup (char*,char const*,char const*) ; 

char *xdg_cache_home(const char *filename)
{
	const char *home, *cache_home;

	assert(filename);
	cache_home = getenv("XDG_CACHE_HOME");
	if (cache_home && *cache_home)
		return mkpathdup("%s/git/%s", cache_home, filename);

	home = getenv("HOME");
	if (home)
		return mkpathdup("%s/.cache/git/%s", home, filename);
	return NULL;
}