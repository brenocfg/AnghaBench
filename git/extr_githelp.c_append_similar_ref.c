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
struct similar_ref_cb {int /*<<< orphan*/  similar_refs; int /*<<< orphan*/  base_ref; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int append_similar_ref(const char *refname, const struct object_id *oid,
			      int flags, void *cb_data)
{
	struct similar_ref_cb *cb = (struct similar_ref_cb *)(cb_data);
	char *branch = strrchr(refname, '/') + 1;
	const char *remote;

	/* A remote branch of the same name is deemed similar */
	if (skip_prefix(refname, "refs/remotes/", &remote) &&
	    !strcmp(branch, cb->base_ref))
		string_list_append(cb->similar_refs, remote);
	return 0;
}