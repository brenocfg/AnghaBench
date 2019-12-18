#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* sv; } ;
struct TYPE_5__ {int type; size_t len; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;

/* Variables and functions */
#define  UCL_STRING 128 

bool
ucl_object_tolstring_safe (const ucl_object_t *obj, const char **target, size_t *tlen)
{
	if (obj == NULL || target == NULL) {
		return false;
	}
	switch (obj->type) {
	case UCL_STRING:
		*target = obj->value.sv;
		if (tlen != NULL) {
			*tlen = obj->len;
		}
		break;
	default:
		return false;
	}

	return true;
}