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
 int /*<<< orphan*/  jw_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jw_object_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jw_object_intmax (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  jw_object_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  jw_object_true (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obj1 ; 

__attribute__((used)) static void make_obj1(int pretty)
{
	jw_object_begin(&obj1, pretty);
	{
		jw_object_string(&obj1, "a", "abc");
		jw_object_intmax(&obj1, "b", 42);
		jw_object_true(&obj1, "c");
	}
	jw_end(&obj1);
}