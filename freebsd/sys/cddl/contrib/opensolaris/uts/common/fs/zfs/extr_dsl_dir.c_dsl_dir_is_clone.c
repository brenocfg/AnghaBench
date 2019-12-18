#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* dd_pool; } ;
typedef  TYPE_3__ dsl_dir_t ;
typedef  int boolean_t ;
struct TYPE_10__ {scalar_t__ dd_origin_obj; } ;
struct TYPE_8__ {TYPE_1__* dp_origin_snap; } ;
struct TYPE_7__ {scalar_t__ ds_object; } ;

/* Variables and functions */
 TYPE_4__* dsl_dir_phys (TYPE_3__*) ; 

boolean_t
dsl_dir_is_clone(dsl_dir_t *dd)
{
	return (dsl_dir_phys(dd)->dd_origin_obj &&
	    (dd->dd_pool->dp_origin_snap == NULL ||
	    dsl_dir_phys(dd)->dd_origin_obj !=
	    dd->dd_pool->dp_origin_snap->ds_object));
}