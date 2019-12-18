#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ref; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ucl_object_dtor_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ucl_object_dtor_unref_single (TYPE_1__*) ; 

__attribute__((used)) static void
ucl_object_dtor_unref (ucl_object_t *obj)
{
	if (obj->ref == 0) {
		ucl_object_dtor_free (obj);
	}
	else {
		/* This may cause dtor unref being called one more time */
		ucl_object_dtor_unref_single (obj);
	}
}