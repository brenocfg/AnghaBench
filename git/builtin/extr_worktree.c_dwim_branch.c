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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UNLEAK (char const*) ; 
 scalar_t__ guess_remote ; 
 scalar_t__ ref_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_check_branch_ref (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* unique_tracking_name (char const*,struct object_id*,int /*<<< orphan*/ *) ; 
 char* worktree_basename (char const*,int*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static const char *dwim_branch(const char *path, const char **new_branch)
{
	int n;
	const char *s = worktree_basename(path, &n);
	const char *branchname = xstrndup(s, n);
	struct strbuf ref = STRBUF_INIT;

	UNLEAK(branchname);
	if (!strbuf_check_branch_ref(&ref, branchname) &&
	    ref_exists(ref.buf)) {
		strbuf_release(&ref);
		return branchname;
	}

	*new_branch = branchname;
	if (guess_remote) {
		struct object_id oid;
		const char *remote =
			unique_tracking_name(*new_branch, &oid, NULL);
		return remote;
	}
	return NULL;
}