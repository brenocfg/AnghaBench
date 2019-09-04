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
typedef  int /*<<< orphan*/  hashmap_cmp_fn ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ path_and_oids_cmp ; 

__attribute__((used)) static void paths_and_oids_init(struct hashmap *map)
{
	hashmap_init(map, (hashmap_cmp_fn) path_and_oids_cmp, NULL, 0);
}