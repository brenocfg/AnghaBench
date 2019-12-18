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
struct tftp_handle {struct tftp_handle* pkt; struct tftp_handle* path; } ;
struct open_file {struct tftp_handle* f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tftp_handle*) ; 
 scalar_t__ is_open ; 

__attribute__((used)) static int
tftp_close(struct open_file *f)
{
	struct tftp_handle *tftpfile;
	tftpfile = f->f_fsdata;

	/* let it time out ... */

	if (tftpfile) {
		free(tftpfile->path);
		free(tftpfile->pkt);
		free(tftpfile);
	}
	is_open = 0;
	return (0);
}