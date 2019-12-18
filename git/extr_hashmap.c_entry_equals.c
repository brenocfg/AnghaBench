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
struct hashmap_entry {scalar_t__ hash; } ;
struct hashmap {int /*<<< orphan*/  cmpfn_data; int /*<<< orphan*/  (* cmpfn ) (int /*<<< orphan*/ ,struct hashmap_entry const*,struct hashmap_entry const*,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct hashmap_entry const*,struct hashmap_entry const*,void const*) ; 

__attribute__((used)) static inline int entry_equals(const struct hashmap *map,
		const struct hashmap_entry *e1, const struct hashmap_entry *e2,
		const void *keydata)
{
	return (e1 == e2) ||
	       (e1->hash == e2->hash &&
		!map->cmpfn(map->cmpfn_data, e1, e2, keydata));
}