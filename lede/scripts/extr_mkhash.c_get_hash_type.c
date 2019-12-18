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
struct hash_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hash_type*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct hash_type* types ; 

__attribute__((used)) static struct hash_type *get_hash_type(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(types); i++) {
		struct hash_type *t = &types[i];

		if (!strcmp(t->name, name))
			return t;
	}
	return NULL;
}