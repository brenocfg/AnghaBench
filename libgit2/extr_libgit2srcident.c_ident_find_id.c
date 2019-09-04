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
 int GIT_ENOTFOUND ; 
 char* memchr (char const*,char,size_t) ; 

__attribute__((used)) static int ident_find_id(
	const char **id_start, const char **id_end, const char *start, size_t len)
{
	const char *end = start + len, *found = NULL;

	while (len > 3 && (found = memchr(start, '$', len)) != NULL) {
		size_t remaining = (size_t)(end - found) - 1;
		if (remaining < 3)
			return GIT_ENOTFOUND;

		start = found + 1;
		len   = remaining;

		if (start[0] == 'I' && start[1] == 'd')
			break;
	}

	if (len < 3 || !found)
		return GIT_ENOTFOUND;
	*id_start = found;

	if ((found = memchr(start + 2, '$', len - 2)) == NULL)
		return GIT_ENOTFOUND;

	*id_end = found + 1;
	return 0;
}