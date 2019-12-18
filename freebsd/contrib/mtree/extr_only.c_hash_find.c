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
typedef  size_t uint32_t ;
struct hentry {size_t hash; int /*<<< orphan*/  str; struct hentry* next; } ;

/* Variables and functions */
 size_t __arraycount (struct hentry**) ; 
 size_t hash_str (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct hentry** table ; 

__attribute__((used)) static bool
hash_find(const char *str, uint32_t *h)
{
	struct hentry *e;
	*h = hash_str(str) % __arraycount(table);

	for (e = table[*h]; e; e = e->next)
		if (e->hash == *h && strcmp(e->str, str) == 0)
			return true;
	return false;
}