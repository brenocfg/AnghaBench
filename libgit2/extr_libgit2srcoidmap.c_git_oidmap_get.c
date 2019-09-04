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
typedef  int /*<<< orphan*/  git_oidmap ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 size_t kh_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_exist (int /*<<< orphan*/ *,size_t) ; 
 size_t kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* kh_val (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  oid ; 

void *git_oidmap_get(git_oidmap *map, const git_oid *key)
{
	size_t idx = kh_get(oid, map, key);
	if (idx == kh_end(map) || !kh_exist(map, idx))
		return NULL;
	return kh_val(map, idx);
}