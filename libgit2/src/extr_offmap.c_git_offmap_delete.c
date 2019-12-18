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
typedef  int /*<<< orphan*/  git_offmap ;
typedef  int /*<<< orphan*/  git_off_t ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  off ; 

int git_offmap_delete(git_offmap *map, const git_off_t key)
{
	khiter_t idx = kh_get(off, map, key);
	if (idx == kh_end(map))
		return GIT_ENOTFOUND;
	kh_del(off, map, idx);
	return 0;
}