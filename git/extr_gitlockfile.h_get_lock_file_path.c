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
 char const* get_tempfile_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *get_lock_file_path(struct lock_file *lk)
{
	return get_tempfile_path(lk->tempfile);
}