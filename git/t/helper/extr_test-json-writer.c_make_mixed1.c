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

/* Variables and functions */
 int /*<<< orphan*/  arr1 ; 
 int /*<<< orphan*/  jw_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_object_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_object_sub_jw (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_arr1 (int) ; 
 int /*<<< orphan*/  make_obj1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixed1 ; 
 int /*<<< orphan*/  obj1 ; 

__attribute__((used)) static void make_mixed1(int pretty)
{
	jw_init(&obj1);
	jw_init(&arr1);

	make_obj1(0); /* obj1 is compact */
	make_arr1(1); /* arr1 is pretty */

	jw_object_begin(&mixed1, pretty);
	{
		jw_object_sub_jw(&mixed1, "obj1", &obj1);
		jw_object_sub_jw(&mixed1, "arr1", &arr1);
	}
	jw_end(&mixed1);
}