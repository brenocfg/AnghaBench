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
 int /*<<< orphan*/  obj2 ; 

__attribute__((used)) static void make_obj2(int pretty)
{
	jw_object_begin(&obj2, pretty);
	{
		jw_object_intmax(&obj2, "a", -1);
		jw_object_intmax(&obj2, "b", 0x7fffffff);
		jw_object_intmax(&obj2, "c", 0);
	}
	jw_end(&obj2);
}