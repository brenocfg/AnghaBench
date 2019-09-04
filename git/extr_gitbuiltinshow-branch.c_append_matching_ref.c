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
struct object_id {int dummy; } ;

/* Variables and functions */
 int append_head_ref (char const*,struct object_id const*,int,void*) ; 
 int append_ref (char const*,struct object_id const*,int /*<<< orphan*/ ) ; 
 int append_tag_ref (char const*,struct object_id const*,int,void*) ; 
 int count_slashes (char const*) ; 
 int /*<<< orphan*/  match_ref_pattern ; 
 int match_ref_slash ; 
 scalar_t__ starts_with (char const*,char*) ; 
 scalar_t__ wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int append_matching_ref(const char *refname, const struct object_id *oid,
			       int flag, void *cb_data)
{
	/* we want to allow pattern hold/<asterisk> to show all
	 * branches under refs/heads/hold/, and v0.99.9? to show
	 * refs/tags/v0.99.9a and friends.
	 */
	const char *tail;
	int slash = count_slashes(refname);
	for (tail = refname; *tail && match_ref_slash < slash; )
		if (*tail++ == '/')
			slash--;
	if (!*tail)
		return 0;
	if (wildmatch(match_ref_pattern, tail, 0))
		return 0;
	if (starts_with(refname, "refs/heads/"))
		return append_head_ref(refname, oid, flag, cb_data);
	if (starts_with(refname, "refs/tags/"))
		return append_tag_ref(refname, oid, flag, cb_data);
	return append_ref(refname, oid, 0);
}