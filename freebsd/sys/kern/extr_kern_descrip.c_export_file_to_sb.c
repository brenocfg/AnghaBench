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
struct file {int dummy; } ;
struct export_fd_buf {scalar_t__ remainder; int /*<<< orphan*/  fdp; int /*<<< orphan*/  flags; int /*<<< orphan*/  kif; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_SLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_file_to_kinfo (struct file*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int export_kinfo_to_sb (struct export_fd_buf*) ; 

__attribute__((used)) static int
export_file_to_sb(struct file *fp, int fd, cap_rights_t *rightsp,
    struct export_fd_buf *efbuf)
{
	int error;

	if (efbuf->remainder == 0)
		return (0);
	export_file_to_kinfo(fp, fd, rightsp, &efbuf->kif, efbuf->fdp,
	    efbuf->flags);
	FILEDESC_SUNLOCK(efbuf->fdp);
	error = export_kinfo_to_sb(efbuf);
	FILEDESC_SLOCK(efbuf->fdp);
	return (error);
}