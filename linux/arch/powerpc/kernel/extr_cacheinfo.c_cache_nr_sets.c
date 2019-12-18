#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {size_t type; int /*<<< orphan*/  ofnode; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {char* nr_sets_prop; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* cache_type_info ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 unsigned int of_read_number (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int cache_nr_sets(const struct cache *cache, unsigned int *ret)
{
	const char *propname;
	const __be32 *nr_sets;

	propname = cache_type_info[cache->type].nr_sets_prop;

	nr_sets = of_get_property(cache->ofnode, propname, NULL);
	if (!nr_sets)
		return -ENODEV;

	*ret = of_read_number(nr_sets, 1);
	return 0;
}