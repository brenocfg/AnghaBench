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
 int /*<<< orphan*/  UCL_ARRAY ; 
 int nelt ; 
 int pcg32_random () ; 
 int /*<<< orphan*/  ucl_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_object_frombool (int) ; 
 int /*<<< orphan*/ * ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t*
ucl_test_boolean (void)
{
	ucl_object_t *res;
	int count, i;

	res = ucl_object_typed_new (UCL_ARRAY);
	count = pcg32_random () % nelt;

	for (i = 0; i < count; i ++) {
		ucl_array_append (res, ucl_object_frombool (pcg32_random () % 2));
	}

	return res;
}