#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {unsigned int is_merge; void* remote_url; void* ref_name; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_fetchhead_ref ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__malloc (int) ; 
 void* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

int git_fetchhead_ref_create(
	git_fetchhead_ref **out,
	git_oid *oid,
	unsigned int is_merge,
	const char *ref_name,
	const char *remote_url)
{
	git_fetchhead_ref *fetchhead_ref;

	assert(out && oid);

	*out = NULL;

	fetchhead_ref = git__malloc(sizeof(git_fetchhead_ref));
	GIT_ERROR_CHECK_ALLOC(fetchhead_ref);

	memset(fetchhead_ref, 0x0, sizeof(git_fetchhead_ref));

	git_oid_cpy(&fetchhead_ref->oid, oid);
	fetchhead_ref->is_merge = is_merge;

	if (ref_name)
		fetchhead_ref->ref_name = git__strdup(ref_name);

	if (remote_url)
		fetchhead_ref->remote_url = git__strdup(remote_url);

	*out = fetchhead_ref;

	return 0;
}