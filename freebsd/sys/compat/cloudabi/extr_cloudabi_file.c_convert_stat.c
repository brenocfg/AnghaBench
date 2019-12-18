#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
typedef  TYPE_1__ cloudabi_filestat_t ;

/* Variables and functions */
 int /*<<< orphan*/  cloudabi_convert_timespec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
convert_stat(const struct stat *sb, cloudabi_filestat_t *csb)
{
	cloudabi_filestat_t res = {
		.st_dev		= sb->st_dev,
		.st_ino		= sb->st_ino,
		.st_nlink	= sb->st_nlink,
		.st_size	= sb->st_size,
	};

	cloudabi_convert_timespec(&sb->st_atim, &res.st_atim);
	cloudabi_convert_timespec(&sb->st_mtim, &res.st_mtim);
	cloudabi_convert_timespec(&sb->st_ctim, &res.st_ctim);
	*csb = res;
}