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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {int /*<<< orphan*/  parent_ids; } ;
typedef  TYPE_1__ git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  const* git_array_get (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static const git_oid *commit_parent_from_commit(size_t n, void *payload)
{
	const git_commit *commit = (const git_commit *) payload;

	return git_array_get(commit->parent_ids, n);

}