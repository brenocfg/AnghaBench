#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ov; } ;
struct TYPE_8__ {scalar_t__ type; char const* key; size_t keylen; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;

/* Variables and functions */
 scalar_t__ UCL_OBJECT ; 
 TYPE_2__* ucl_hash_search_obj (int /*<<< orphan*/ ,TYPE_2__*) ; 

const ucl_object_t *
ucl_object_lookup_len (const ucl_object_t *obj, const char *key, size_t klen)
{
	const ucl_object_t *ret;
	ucl_object_t srch;

	if (obj == NULL || obj->type != UCL_OBJECT || key == NULL) {
		return NULL;
	}

	srch.key = key;
	srch.keylen = klen;
	ret = ucl_hash_search_obj (obj->value.ov, &srch);

	return ret;
}