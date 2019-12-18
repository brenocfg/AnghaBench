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
struct cache_entry_ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
entries_bsearch_cmp_func(const void *key, const void *ent)
{

	assert(key != NULL);
	assert(ent != NULL);

	return (strcmp((char const *)key,
		(*(struct cache_entry_ const **)ent)->name));
}