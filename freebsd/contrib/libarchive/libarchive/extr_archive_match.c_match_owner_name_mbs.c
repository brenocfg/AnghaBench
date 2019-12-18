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
struct match_list {struct match* first; } ;
struct match {int /*<<< orphan*/  matches; int /*<<< orphan*/  pattern; struct match* next; } ;
struct archive_match {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ archive_mstring_get_mbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ errno ; 
 int error_nomem (struct archive_match*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
match_owner_name_mbs(struct archive_match *a, struct match_list *list,
    const char *name)
{
	struct match *m;
	const char *p;

	if (name == NULL || *name == '\0')
		return (0);
	for (m = list->first; m; m = m->next) {
		if (archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p)
		    < 0 && errno == ENOMEM)
			return (error_nomem(a));
		if (p != NULL && strcmp(p, name) == 0) {
			m->matches++;
			return (1);
		}
	}
	return (0);
}