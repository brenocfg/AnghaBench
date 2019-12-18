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
typedef  int /*<<< orphan*/  ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_STRING_ESCAPE ; 
 int /*<<< orphan*/ * ucl_object_fromstring_common (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ucl_object_t*
ucl_object_fromstring (const char *str)
{
	return ucl_object_fromstring_common (str, 0, UCL_STRING_ESCAPE);
}