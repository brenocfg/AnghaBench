#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_NULL ; 

ucl_type_t
ucl_object_type (const ucl_object_t *obj)
{
	if (obj == NULL) {
		return UCL_NULL;
	}

	return obj->type;
}