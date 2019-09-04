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
struct refspec {int nr; int /*<<< orphan*/ * items; } ;
typedef  struct ref {struct ref const* next; } const ref ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct ref const* copy_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_ref_by_name (struct ref const*,char*) ; 
 int /*<<< orphan*/  find_remote_branch (struct ref const*,scalar_t__) ; 
 int /*<<< orphan*/  get_fetch_map (struct ref const*,int /*<<< orphan*/ *,struct ref const***,int /*<<< orphan*/ ) ; 
 struct ref const* guess_remote_head (struct ref const*,struct ref const*,int /*<<< orphan*/ ) ; 
 scalar_t__ option_branch ; 
 int /*<<< orphan*/  option_mirror ; 
 int /*<<< orphan*/  option_no_tags ; 
 scalar_t__ option_single_branch ; 
 int /*<<< orphan*/ * tag_refspec ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct ref *wanted_peer_refs(const struct ref *refs,
		struct refspec *refspec)
{
	struct ref *head = copy_ref(find_ref_by_name(refs, "HEAD"));
	struct ref *local_refs = head;
	struct ref **tail = head ? &head->next : &local_refs;

	if (option_single_branch) {
		struct ref *remote_head = NULL;

		if (!option_branch)
			remote_head = guess_remote_head(head, refs, 0);
		else {
			local_refs = NULL;
			tail = &local_refs;
			remote_head = copy_ref(find_remote_branch(refs, option_branch));
		}

		if (!remote_head && option_branch)
			warning(_("Could not find remote branch %s to clone."),
				option_branch);
		else {
			int i;
			for (i = 0; i < refspec->nr; i++)
				get_fetch_map(remote_head, &refspec->items[i],
					      &tail, 0);

			/* if --branch=tag, pull the requested tag explicitly */
			get_fetch_map(remote_head, tag_refspec, &tail, 0);
		}
	} else {
		int i;
		for (i = 0; i < refspec->nr; i++)
			get_fetch_map(refs, &refspec->items[i], &tail, 0);
	}

	if (!option_mirror && !option_single_branch && !option_no_tags)
		get_fetch_map(refs, tag_refspec, &tail, 0);

	return local_refs;
}