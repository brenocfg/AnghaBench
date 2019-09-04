#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__** active_cache ; 
 int active_nr ; 
 char* add_slash (char const*) ; 
 int cache_name_pos (char const*,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int index_range_of_same_dir(const char *src, int length,
				   int *first_p, int *last_p)
{
	const char *src_w_slash = add_slash(src);
	int first, last, len_w_slash = length + 1;

	first = cache_name_pos(src_w_slash, len_w_slash);
	if (first >= 0)
		die(_("%.*s is in index"), len_w_slash, src_w_slash);

	first = -1 - first;
	for (last = first; last < active_nr; last++) {
		const char *path = active_cache[last]->name;
		if (strncmp(path, src_w_slash, len_w_slash))
			break;
	}
	if (src_w_slash != src)
		free((char *)src_w_slash);
	*first_p = first;
	*last_p = last;
	return last - first;
}