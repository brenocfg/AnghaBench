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
struct tftp_handle {int /*<<< orphan*/  tftp_tsize; } ;
struct stat {int st_mode; int st_nlink; int /*<<< orphan*/  st_size; scalar_t__ st_gid; scalar_t__ st_uid; } ;
struct open_file {struct tftp_handle* f_fsdata; } ;

/* Variables and functions */
 int S_IFREG ; 

__attribute__((used)) static int
tftp_stat(struct open_file *f, struct stat *sb)
{
	struct tftp_handle *tftpfile;
	tftpfile = f->f_fsdata;

	sb->st_mode = 0444 | S_IFREG;
	sb->st_nlink = 1;
	sb->st_uid = 0;
	sb->st_gid = 0;
	sb->st_size = tftpfile->tftp_tsize;
	return (0);
}