#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t n_buckets; } ;
typedef  TYPE_1__ git_oidmap ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  kh_exist (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/ * kh_key (TYPE_1__*,size_t) ; 
 void* kh_value (TYPE_1__*,size_t) ; 

int git_oidmap_iterate(void **value, git_oidmap *map, size_t *iter, const git_oid **key)
{
	size_t i = *iter;

	while (i < map->n_buckets && !kh_exist(map, i))
		i++;

	if (i >= map->n_buckets)
		return GIT_ITEROVER;

	if (key)
		*key = kh_key(map, i);
	if (value)
		*value = kh_value(map, i);
	*iter = ++i;

	return 0;
}