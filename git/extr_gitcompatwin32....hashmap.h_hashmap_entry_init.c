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
struct hashmap_entry {unsigned int hash; int /*<<< orphan*/ * next; } ;

/* Variables and functions */

__attribute__((used)) static inline void hashmap_entry_init(void *entry, unsigned int hash)
{
	struct hashmap_entry *e = entry;
	e->hash = hash;
	e->next = NULL;
}