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
struct TYPE_4__ {double iv; double dv; } ;
struct TYPE_5__ {int type; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;

/* Variables and functions */
#define  UCL_FLOAT 130 
#define  UCL_INT 129 
#define  UCL_TIME 128 

bool
ucl_object_todouble_safe (const ucl_object_t *obj, double *target)
{
	if (obj == NULL || target == NULL) {
		return false;
	}
	switch (obj->type) {
	case UCL_INT:
		*target = obj->value.iv; /* Probaly could cause overflow */
		break;
	case UCL_FLOAT:
	case UCL_TIME:
		*target = obj->value.dv;
		break;
	default:
		return false;
	}

	return true;
}