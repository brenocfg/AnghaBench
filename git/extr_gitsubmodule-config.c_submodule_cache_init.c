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
struct submodule_cache {int initialized; int /*<<< orphan*/  for_name; int /*<<< orphan*/  for_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_name_cmp ; 
 int /*<<< orphan*/  config_path_cmp ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void submodule_cache_init(struct submodule_cache *cache)
{
	hashmap_init(&cache->for_path, config_path_cmp, NULL, 0);
	hashmap_init(&cache->for_name, config_name_cmp, NULL, 0);
	cache->initialized = 1;
}