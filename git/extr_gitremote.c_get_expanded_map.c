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
struct refspec_item {scalar_t__ force; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct ref {struct ref* next; TYPE_1__* peer_ref; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int force; } ;

/* Variables and functions */
 TYPE_1__* alloc_ref (char*) ; 
 struct ref* copy_ref (struct ref const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_symref_update (char*) ; 
 scalar_t__ match_name_with_pattern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static struct ref *get_expanded_map(const struct ref *remote_refs,
				    const struct refspec_item *refspec)
{
	const struct ref *ref;
	struct ref *ret = NULL;
	struct ref **tail = &ret;

	for (ref = remote_refs; ref; ref = ref->next) {
		char *expn_name = NULL;

		if (strchr(ref->name, '^'))
			continue; /* a dereference item */
		if (match_name_with_pattern(refspec->src, ref->name,
					    refspec->dst, &expn_name) &&
		    !ignore_symref_update(expn_name)) {
			struct ref *cpy = copy_ref(ref);

			cpy->peer_ref = alloc_ref(expn_name);
			if (refspec->force)
				cpy->peer_ref->force = 1;
			*tail = cpy;
			tail = &cpy->next;
		}
		free(expn_name);
	}

	return ret;
}