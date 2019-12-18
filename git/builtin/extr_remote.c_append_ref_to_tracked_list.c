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
struct refspec_item {char* dst; int /*<<< orphan*/  src; } ;
struct ref_states {int /*<<< orphan*/  tracked; int /*<<< orphan*/  remote; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  refspec ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  abbrev_branch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct refspec_item*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remote_find_tracking (int /*<<< orphan*/ ,struct refspec_item*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int append_ref_to_tracked_list(const char *refname,
	const struct object_id *oid, int flags, void *cb_data)
{
	struct ref_states *states = cb_data;
	struct refspec_item refspec;

	if (flags & REF_ISSYMREF)
		return 0;

	memset(&refspec, 0, sizeof(refspec));
	refspec.dst = (char *)refname;
	if (!remote_find_tracking(states->remote, &refspec))
		string_list_append(&states->tracked, abbrev_branch(refspec.src));

	return 0;
}