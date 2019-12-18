#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * configmap_cache; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int GIT_CONFIGMAP_CACHE_MAX ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_NOT_CACHED ; 

void git_repository__configmap_lookup_cache_clear(git_repository *repo)
{
	int i;

	for (i = 0; i < GIT_CONFIGMAP_CACHE_MAX; ++i)
		repo->configmap_cache[i] = GIT_CONFIGMAP_NOT_CACHED;
}