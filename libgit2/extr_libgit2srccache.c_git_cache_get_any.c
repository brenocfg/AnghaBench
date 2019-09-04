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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CACHE_STORE_ANY ; 
 void* cache_get (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void *git_cache_get_any(git_cache *cache, const git_oid *oid)
{
	return cache_get(cache, oid, GIT_CACHE_STORE_ANY);
}