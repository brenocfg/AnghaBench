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
struct common_dir {int /*<<< orphan*/  exclude; scalar_t__ is_dir; } ;

/* Variables and functions */

__attribute__((used)) static int check_common(const char *unmatched, void *value, void *baton)
{
	struct common_dir *dir = value;

	if (!dir)
		return 0;

	if (dir->is_dir && (unmatched[0] == 0 || unmatched[0] == '/'))
		return !dir->exclude;

	if (!dir->is_dir && unmatched[0] == 0)
		return !dir->exclude;

	return 0;
}