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
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_idxmap ;

/* Variables and functions */
 size_t idx ; 
 size_t kh_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_exist (int /*<<< orphan*/ *,size_t) ; 
 size_t kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* kh_val (int /*<<< orphan*/ *,size_t) ; 

void *git_idxmap_get(git_idxmap *map, const git_index_entry *key)
{
	size_t idx = kh_get(idx, map, key);
	if (idx == kh_end(map) || !kh_exist(map, idx))
		return NULL;
	return kh_val(map, idx);
}