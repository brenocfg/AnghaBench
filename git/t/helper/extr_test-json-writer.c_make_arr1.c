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
 int /*<<< orphan*/  jw_array_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_array_intmax (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_array_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_array_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void make_arr1(int pretty)
{
	jw_array_begin(&arr1, pretty);
	{
		jw_array_string(&arr1, "abc");
		jw_array_intmax(&arr1, 42);
		jw_array_true(&arr1);
	}
	jw_end(&arr1);
}