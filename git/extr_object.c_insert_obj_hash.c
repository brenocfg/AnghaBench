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
struct object {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 unsigned int hash_obj (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void insert_obj_hash(struct object *obj, struct object **hash, unsigned int size)
{
	unsigned int j = hash_obj(&obj->oid, size);

	while (hash[j]) {
		j++;
		if (j >= size)
			j = 0;
	}
	hash[j] = obj;
}