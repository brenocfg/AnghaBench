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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ cached; } ;
typedef  TYPE_2__ git_object ;
typedef  int /*<<< orphan*/  git_cached_obj ;
typedef  int /*<<< orphan*/  git_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CACHE_STORE_PARSED ; 
 void* cache_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *git_cache_store_parsed(git_cache *cache, git_object *entry)
{
	entry->cached.flags = GIT_CACHE_STORE_PARSED;
	return cache_store(cache, (git_cached_obj *)entry);
}