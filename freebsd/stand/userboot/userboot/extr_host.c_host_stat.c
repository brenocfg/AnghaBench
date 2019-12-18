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
typedef  int /*<<< orphan*/  uint64_t ;
struct stat {int st_mode; int st_uid; int st_gid; int /*<<< orphan*/  st_size; } ;
struct open_file {int /*<<< orphan*/  f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat ; 

__attribute__((used)) static int
host_stat(struct open_file *f, struct stat *sb)
{
	int mode;
	int uid;
	int gid;
	uint64_t size;

	CALLBACK(stat, f->f_fsdata, &mode, &uid, &gid, &size);
	sb->st_mode = mode;
	sb->st_uid = uid;
	sb->st_gid = gid;
	sb->st_size = size;
	return (0);
}