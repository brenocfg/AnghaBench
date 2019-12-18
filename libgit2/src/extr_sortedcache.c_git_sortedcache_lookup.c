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
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 void* git_strmap_get (int /*<<< orphan*/ ,char const*) ; 

void *git_sortedcache_lookup(const git_sortedcache *sc, const char *key)
{
	return git_strmap_get(sc->map, key);
}