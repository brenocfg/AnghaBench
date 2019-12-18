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
 scalar_t__ ucl_hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const ucl_object_t *
ucl_hash_search_obj (ucl_hash_t* hashlin, ucl_object_t *obj)
{
	return (const ucl_object_t *)ucl_hash_search (hashlin, obj->key, obj->keylen);
}