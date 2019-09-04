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
struct lock_file {int dummy; } ;

/* Variables and functions */
 int hold_lock_file_for_update_timeout (struct lock_file*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hold_lock_file_for_update(
		struct lock_file *lk, const char *path,
		int flags)
{
	return hold_lock_file_for_update_timeout(lk, path, flags, 0);
}