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
typedef  scalar_t__ khiter_t ;
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_idxmap_icase ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  idxicase ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_idxmap_icase_delete(git_idxmap_icase *map, const git_index_entry *key)
{
	khiter_t idx = kh_get(idxicase, map, key);
	if (idx == kh_end(map))
		return GIT_ENOTFOUND;
	kh_del(idxicase, map, idx);
	return 0;
}