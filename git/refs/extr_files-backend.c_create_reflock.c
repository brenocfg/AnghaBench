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
 int /*<<< orphan*/  LOCK_NO_DEREF ; 
 int /*<<< orphan*/  get_files_ref_lock_timeout_ms () ; 
 scalar_t__ hold_lock_file_for_update_timeout (struct lock_file*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_reflock(const char *path, void *cb)
{
	struct lock_file *lk = cb;

	return hold_lock_file_for_update_timeout(
			lk, path, LOCK_NO_DEREF,
			get_files_ref_lock_timeout_ms()) < 0 ? -1 : 0;
}