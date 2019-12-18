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
 int /*<<< orphan*/  autofs_readdir_one (int /*<<< orphan*/ *,char const*,int,size_t*) ; 

__attribute__((used)) static size_t
autofs_dirent_reclen(const char *name)
{
	size_t reclen;

	(void)autofs_readdir_one(NULL, name, -1, &reclen);

	return (reclen);
}