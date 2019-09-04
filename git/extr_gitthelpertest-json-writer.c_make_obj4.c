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
 int /*<<< orphan*/  jw_object_false (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_object_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jw_object_true (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obj4 ; 

__attribute__((used)) static void make_obj4(int pretty)
{
	jw_object_begin(&obj4, pretty);
	{
		jw_object_true(&obj4, "t");
		jw_object_false(&obj4, "f");
		jw_object_null(&obj4, "n");
	}
	jw_end(&obj4);
}