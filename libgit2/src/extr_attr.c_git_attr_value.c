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
typedef  int /*<<< orphan*/  git_attr_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_VALUE_FALSE ; 
 int /*<<< orphan*/  GIT_ATTR_VALUE_STRING ; 
 int /*<<< orphan*/  GIT_ATTR_VALUE_TRUE ; 
 int /*<<< orphan*/  GIT_ATTR_VALUE_UNSPECIFIED ; 
 char const* git_attr__false ; 
 char const* git_attr__true ; 
 char const* git_attr__unset ; 

git_attr_value_t git_attr_value(const char *attr)
{
	if (attr == NULL || attr == git_attr__unset)
		return GIT_ATTR_VALUE_UNSPECIFIED;

	if (attr == git_attr__true)
		return GIT_ATTR_VALUE_TRUE;

	if (attr == git_attr__false)
		return GIT_ATTR_VALUE_FALSE;

	return GIT_ATTR_VALUE_STRING;
}