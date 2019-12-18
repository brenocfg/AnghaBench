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
typedef  int /*<<< orphan*/  ucl_object_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_ITERATE_BOTH ; 
 int /*<<< orphan*/  UCL_ITERATE_IMPLICIT ; 
 int /*<<< orphan*/  const* ucl_object_iterate_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const ucl_object_t*
ucl_object_iterate_safe (ucl_object_iter_t it, bool expand_values)
{
	return ucl_object_iterate_full (it, expand_values ? UCL_ITERATE_BOTH :
			UCL_ITERATE_IMPLICIT);
}