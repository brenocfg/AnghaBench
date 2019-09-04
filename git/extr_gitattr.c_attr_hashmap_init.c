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
struct attr_hashmap {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_hash_entry_cmp ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void attr_hashmap_init(struct attr_hashmap *map)
{
	hashmap_init(&map->map, attr_hash_entry_cmp, NULL, 0);
}