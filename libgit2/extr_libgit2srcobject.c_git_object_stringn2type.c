#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_object_t ;
struct TYPE_3__ {scalar_t__* str; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_OBJECT_INVALID ; 
 int /*<<< orphan*/  git__prefixncmp (char const*,size_t,scalar_t__*) ; 
 TYPE_1__* git_objects_table ; 

git_object_t git_object_stringn2type(const char *str, size_t len)
{
	size_t i;

	if (!str || !len || !*str)
		return GIT_OBJECT_INVALID;

	for (i = 0; i < ARRAY_SIZE(git_objects_table); i++)
		if (*git_objects_table[i].str &&
			!git__prefixncmp(str, len, git_objects_table[i].str))
			return (git_object_t)i;

	return GIT_OBJECT_INVALID;
}