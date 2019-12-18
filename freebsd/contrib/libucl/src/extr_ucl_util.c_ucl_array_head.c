#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * av; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;
struct TYPE_10__ {scalar_t__ n; TYPE_2__ const** a; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_ARRAY_GET (TYPE_3__*,TYPE_2__ const*) ; 
 TYPE_3__* vec ; 

const ucl_object_t *
ucl_array_head (const ucl_object_t *top)
{
	UCL_ARRAY_GET (vec, top);

	if (vec == NULL || top == NULL || top->type != UCL_ARRAY ||
			top->value.av == NULL) {
		return NULL;
	}

	return (vec->n > 0 ? vec->a[0] : NULL);
}