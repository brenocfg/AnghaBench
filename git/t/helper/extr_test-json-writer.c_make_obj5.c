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
 int /*<<< orphan*/  jw_object_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obj5 ; 

__attribute__((used)) static void make_obj5(int pretty)
{
	jw_object_begin(&obj5, pretty);
	{
		jw_object_string(&obj5, "abc" "\x09" "def", "abc" "\\" "def");
	}
	jw_end(&obj5);
}