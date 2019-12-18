#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  expected_oids; TYPE_1__* pack; int /*<<< orphan*/  odb; } ;
typedef  TYPE_2__ git_indexer ;
struct TYPE_4__ {int /*<<< orphan*/  idx_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 int /*<<< orphan*/  git_odb_exists (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oidmap_exists (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_expected_oid(git_indexer *idx, const git_oid *oid)
{
	/*
	 * If we know about that object because it is stored in our ODB or
	 * because we have already processed it as part of our pack file, we do
	 * not have to expect it.
	 */
	if ((!idx->odb || !git_odb_exists(idx->odb, oid)) &&
	    !git_oidmap_exists(idx->pack->idx_cache, oid) &&
	    !git_oidmap_exists(idx->expected_oids, oid)) {
		    git_oid *dup = git__malloc(sizeof(*oid));
		    GIT_ERROR_CHECK_ALLOC(dup);
		    git_oid_cpy(dup, oid);
		    return git_oidmap_set(idx->expected_oids, dup, dup);
	}

	return 0;
}