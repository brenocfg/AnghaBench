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
 int /*<<< orphan*/  ucl_object_toboolean_safe (int /*<<< orphan*/  const*,int*) ; 

bool
ucl_object_toboolean (const ucl_object_t *obj)
{
	bool result = false;

	ucl_object_toboolean_safe (obj, &result);
	return result;
}