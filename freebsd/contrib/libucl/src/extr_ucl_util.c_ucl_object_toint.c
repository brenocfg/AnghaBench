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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ucl_object_toint_safe (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int64_t
ucl_object_toint (const ucl_object_t *obj)
{
	int64_t result = 0;

	ucl_object_toint_safe (obj, &result);
	return result;
}