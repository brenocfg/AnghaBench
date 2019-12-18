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
struct TYPE_4__ {scalar_t__ keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int
ucl_hash_equal (const ucl_object_t *k1, const ucl_object_t *k2)
{
	if (k1->keylen == k2->keylen) {
		return memcmp (k1->key, k2->key, k1->keylen) == 0;
	}

	return 0;
}