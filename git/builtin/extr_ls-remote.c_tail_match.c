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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  wildmatch (char const*,char*,int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static int tail_match(const char **pattern, const char *path)
{
	const char *p;
	char *pathbuf;

	if (!pattern)
		return 1; /* no restriction */

	pathbuf = xstrfmt("/%s", path);
	while ((p = *(pattern++)) != NULL) {
		if (!wildmatch(p, pathbuf, 0)) {
			free(pathbuf);
			return 1;
		}
	}
	free(pathbuf);
	return 0;
}