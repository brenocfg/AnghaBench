#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/  ucl_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ucl_hash_create (int) ; 
 int /*<<< orphan*/  ucl_hash_insert (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ucl_hash_t *
ucl_hash_insert_object (ucl_hash_t *hashlin,
		const ucl_object_t *obj,
		bool ignore_case)
{
	if (hashlin == NULL) {
		hashlin = ucl_hash_create (ignore_case);
	}
	ucl_hash_insert (hashlin, obj, obj->key, obj->keylen);

	return hashlin;
}