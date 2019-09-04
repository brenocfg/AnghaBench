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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ git_oid_strcmp (int /*<<< orphan*/  const*,char const*) ; 

int git_oid_streq(const git_oid *oid_a, const char *str)
{
	return git_oid_strcmp(oid_a, str) == 0 ? 0 : -1;
}