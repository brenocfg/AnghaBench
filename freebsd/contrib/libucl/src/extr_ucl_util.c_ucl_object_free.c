#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ucl_object_dtor_free ; 
 int /*<<< orphan*/  ucl_object_free_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
ucl_object_free (ucl_object_t *obj)
{
	ucl_object_free_internal (obj, true, ucl_object_dtor_free);
}