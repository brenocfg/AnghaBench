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
struct tftp_handle {int off; } ;
struct open_file {struct tftp_handle* f_fsdata; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOFFSET ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static off_t
tftp_seek(struct open_file *f, off_t offset, int where)
{
	struct tftp_handle *tftpfile;
	tftpfile = f->f_fsdata;

	switch (where) {
	case SEEK_SET:
		tftpfile->off = offset;
		break;
	case SEEK_CUR:
		tftpfile->off += offset;
		break;
	default:
		errno = EOFFSET;
		return (-1);
	}
	return (tftpfile->off);
}