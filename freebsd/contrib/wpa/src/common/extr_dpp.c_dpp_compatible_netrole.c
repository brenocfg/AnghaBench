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
 scalar_t__ os_strcmp (char const*,char*) ; 

__attribute__((used)) static int dpp_compatible_netrole(const char *role1, const char *role2)
{
	return (os_strcmp(role1, "sta") == 0 && os_strcmp(role2, "ap") == 0) ||
		(os_strcmp(role1, "ap") == 0 && os_strcmp(role2, "sta") == 0);
}