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
struct tempfile {int fd; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 

int close_tempfile_gently(struct tempfile *tempfile)
{
	int fd;
	FILE *fp;
	int err;

	if (!is_tempfile_active(tempfile) || tempfile->fd < 0)
		return 0;

	fd = tempfile->fd;
	fp = tempfile->fp;
	tempfile->fd = -1;
	if (fp) {
		tempfile->fp = NULL;
		if (ferror(fp)) {
			err = -1;
			if (!fclose(fp))
				errno = EIO;
		} else {
			err = fclose(fp);
		}
	} else {
		err = close(fd);
	}

	return err ? -1 : 0;
}