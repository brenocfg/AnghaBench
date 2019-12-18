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
 int /*<<< orphan*/  obj3 ; 

__attribute__((used)) static void make_obj3(int pretty)
{
	jw_object_begin(&obj3, pretty);
	{
		jw_object_intmax(&obj3, "a", 0);
		jw_object_intmax(&obj3, "b", 0xffffffff);
		jw_object_intmax(&obj3, "c", 0x7fffffffffffffffULL);
	}
	jw_end(&obj3);
}