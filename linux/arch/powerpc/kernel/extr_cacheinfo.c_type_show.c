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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct cache {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* cache_type_string (struct cache*) ; 
 struct cache* index_kobj_to_cache (struct kobject*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t type_show(struct kobject *k, struct kobj_attribute *attr, char *buf)
{
	struct cache *cache;

	cache = index_kobj_to_cache(k);

	return sprintf(buf, "%s\n", cache_type_string(cache));
}