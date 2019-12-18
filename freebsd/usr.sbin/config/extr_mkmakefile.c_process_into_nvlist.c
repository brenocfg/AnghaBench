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

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ preprocess (char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
process_into_nvlist(char *line, nvlist_t *nvl)
{
	char result[BUFSIZ], *s;

	if (preprocess(line, result)) {
		s = strchr(result, '=');
		*s = '\0';
		if (nvlist_exists(nvl, result))
			nvlist_free(nvl, result);
		nvlist_add_string(nvl, result, s + 1);
	}
}