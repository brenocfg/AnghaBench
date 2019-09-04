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
 int /*<<< orphan*/  default_cache ; 
 int threaded_has_symlink_leading_path (int /*<<< orphan*/ *,char const*,int) ; 

int has_symlink_leading_path(const char *name, int len)
{
	return threaded_has_symlink_leading_path(&default_cache, name, len);
}