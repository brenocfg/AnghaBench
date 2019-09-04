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
typedef  struct git_attr {int attr_nr; int /*<<< orphan*/  name; } const git_attr ;
struct TYPE_6__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct git_attr const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  attr_hashmap_add (TYPE_1__*,int /*<<< orphan*/ ,int,struct git_attr const*) ; 
 struct git_attr const* attr_hashmap_get (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  attr_name_valid (char const*,int) ; 
 TYPE_1__ g_attr_hashmap ; 
 int hashmap_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_unlock (TYPE_1__*) ; 

__attribute__((used)) static const struct git_attr *git_attr_internal(const char *name, int namelen)
{
	struct git_attr *a;

	if (!attr_name_valid(name, namelen))
		return NULL;

	hashmap_lock(&g_attr_hashmap);

	a = attr_hashmap_get(&g_attr_hashmap, name, namelen);

	if (!a) {
		FLEX_ALLOC_MEM(a, name, name, namelen);
		a->attr_nr = hashmap_get_size(&g_attr_hashmap.map);

		attr_hashmap_add(&g_attr_hashmap, a->name, namelen, a);
		assert(a->attr_nr ==
		       (hashmap_get_size(&g_attr_hashmap.map) - 1));
	}

	hashmap_unlock(&g_attr_hashmap);

	return a;
}