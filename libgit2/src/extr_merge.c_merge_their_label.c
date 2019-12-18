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
 char* strrchr (char const*,char) ; 

const char *merge_their_label(const char *branchname)
{
	const char *slash;

	if ((slash = strrchr(branchname, '/')) == NULL)
		return branchname;

	if (*(slash+1) == '\0')
		return "theirs";

	return slash+1;
}