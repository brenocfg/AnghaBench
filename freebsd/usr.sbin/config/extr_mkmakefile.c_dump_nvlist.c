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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cnvlist_free_string (void*) ; 
 char* cnvlist_get_string (void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 char* nvlist_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void
dump_nvlist(nvlist_t *nvl, FILE *ofp)
{
	const char *name;
	void *cookie;

	if (nvl == NULL)
		return;

	while (!nvlist_empty(nvl)) {
		cookie = NULL;
		name = nvlist_next(nvl, NULL, &cookie);
		fprintf(ofp, "\"%s=%s\\0\"\n", name,
		     cnvlist_get_string(cookie));

		cnvlist_free_string(cookie);
	}
}