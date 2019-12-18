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
 int /*<<< orphan*/ * ucl_object_fromstring_common (char const*,size_t,int /*<<< orphan*/ ) ; 

ucl_object_t *
ucl_object_fromlstring (const char *str, size_t len)
{
	return ucl_object_fromstring_common (str, len, UCL_STRING_ESCAPE);
}