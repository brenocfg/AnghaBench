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
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_get_from_hash (struct hashmap*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strhash (char const*) ; 

__attribute__((used)) static int refname_hash_exists(struct hashmap *map, const char *refname)
{
	return !!hashmap_get_from_hash(map, strhash(refname), refname);
}