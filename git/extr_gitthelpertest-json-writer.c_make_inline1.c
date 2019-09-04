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
 int /*<<< orphan*/  inline1 ; 
 int /*<<< orphan*/  jw_array_intmax (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_array_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_array_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_object_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_object_inline_begin_array (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_object_inline_begin_object (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_object_intmax (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  jw_object_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  jw_object_true (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void make_inline1(int pretty)
{
	jw_object_begin(&inline1, pretty);
	{
		jw_object_inline_begin_object(&inline1, "obj1");
		{
			jw_object_string(&inline1, "a", "abc");
			jw_object_intmax(&inline1, "b", 42);
			jw_object_true(&inline1, "c");
		}
		jw_end(&inline1);
		jw_object_inline_begin_array(&inline1, "arr1");
		{
			jw_array_string(&inline1, "abc");
			jw_array_intmax(&inline1, 42);
			jw_array_true(&inline1);
		}
		jw_end(&inline1);
	}
	jw_end(&inline1);
}