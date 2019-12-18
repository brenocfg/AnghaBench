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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ CAT_guide ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static const char *drop_prefix(const char *name, uint32_t category)
{
	const char *new_name;

	if (skip_prefix(name, "git-", &new_name))
		return new_name;
	if (category == CAT_guide && skip_prefix(name, "git", &new_name))
		return new_name;
	return name;

}