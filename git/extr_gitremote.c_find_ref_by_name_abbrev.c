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
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 int refname_match (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct ref *find_ref_by_name_abbrev(const struct ref *refs, const char *name)
{
	const struct ref *ref;
	const struct ref *best_match = NULL;
	int best_score = 0;

	for (ref = refs; ref; ref = ref->next) {
		int score = refname_match(name, ref->name);

		if (best_score < score) {
			best_match = ref;
			best_score = score;
		}
	}
	return best_match;
}