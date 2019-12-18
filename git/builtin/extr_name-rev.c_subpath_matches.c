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
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  wildmatch (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subpath_matches(const char *path, const char *filter)
{
	const char *subpath = path;

	while (subpath) {
		if (!wildmatch(filter, subpath, 0))
			return subpath - path;
		subpath = strchr(subpath, '/');
		if (subpath)
			subpath++;
	}
	return -1;
}