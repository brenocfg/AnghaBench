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
struct ref_array_item {char* refname; scalar_t__ kind; } ;
struct ref_array {int nr; struct ref_array_item** items; } ;

/* Variables and functions */
 scalar_t__ FILTER_REFS_DETACHED_HEAD ; 
 scalar_t__ FILTER_REFS_REMOTES ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_head_description () ; 
 int /*<<< orphan*/  skip_prefix (char*,char*,char const**) ; 
 int utf8_strwidth (char const*) ; 

__attribute__((used)) static int calc_maxwidth(struct ref_array *refs, int remote_bonus)
{
	int i, max = 0;
	for (i = 0; i < refs->nr; i++) {
		struct ref_array_item *it = refs->items[i];
		const char *desc = it->refname;
		int w;

		skip_prefix(it->refname, "refs/heads/", &desc);
		skip_prefix(it->refname, "refs/remotes/", &desc);
		if (it->kind == FILTER_REFS_DETACHED_HEAD) {
			char *head_desc = get_head_description();
			w = utf8_strwidth(head_desc);
			free(head_desc);
		} else
			w = utf8_strwidth(desc);

		if (it->kind == FILTER_REFS_REMOTES)
			w += remote_bonus;
		if (w > max)
			max = w;
	}
	return max;
}