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
 int /*<<< orphan*/  inline2 ; 
 int /*<<< orphan*/  jw_array_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_array_inline_begin_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_array_inline_begin_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_array_intmax (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_object_string (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void make_inline2(int pretty)
{
	jw_array_begin(&inline2, pretty);
	{
		jw_array_inline_begin_array(&inline2);
		{
			jw_array_intmax(&inline2, 1);
			jw_array_intmax(&inline2, 2);
		}
		jw_end(&inline2);
		jw_array_inline_begin_array(&inline2);
		{
			jw_array_intmax(&inline2, 3);
			jw_array_intmax(&inline2, 4);
		}
		jw_end(&inline2);
		jw_array_inline_begin_object(&inline2);
		{
			jw_object_string(&inline2, "a", "abc");
		}
		jw_end(&inline2);
	}
	jw_end(&inline2);
}