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
struct lock_file {int /*<<< orphan*/  tempfile; } ;

/* Variables and functions */
 int rename_tempfile (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline int commit_lock_file_to(struct lock_file *lk, const char *path)
{
	return rename_tempfile(&lk->tempfile, path);
}