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
 int /*<<< orphan*/  jw_object_double (int /*<<< orphan*/ *,char*,int,double) ; 
 int /*<<< orphan*/  obj6 ; 

__attribute__((used)) static void make_obj6(int pretty)
{
	jw_object_begin(&obj6, pretty);
	{
		jw_object_double(&obj6, "a", 2, 3.14159);
	}
	jw_end(&obj6);
}