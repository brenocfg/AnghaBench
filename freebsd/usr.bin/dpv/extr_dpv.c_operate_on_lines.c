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
struct dpv_file_node {int read; scalar_t__ length; int /*<<< orphan*/  status; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPV_STATUS_DONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  bsize ; 
 char* buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dpv_overall_read ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int fd ; 
 int /*<<< orphan*/  fsync (int) ; 
 scalar_t__ no_overrun ; 
 scalar_t__ operate_common (struct dpv_file_node*,int) ; 
 size_t read (int,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 size_t write (int,char*,size_t) ; 

__attribute__((used)) static int
operate_on_lines(struct dpv_file_node *file, int out)
{
	char *p;
	int progress;
	ssize_t r, w;

	if (operate_common(file, out) < 0)
		return (-1);

	/* [Re-]Fill the buffer */
	if ((r = read(fd, buf, bsize)) <= 0) {
		if (fd != STDIN_FILENO)
			close(fd);
		fd = -1;
		file->status = DPV_STATUS_DONE;
		return (100);
	}
	buf[r] = '\0';

	/* [Re-]Dump the buffer */
	if (out >= 0) {
		if ((w = write(out, buf, r)) < 0) {
			end_dialog();
			err(EXIT_FAILURE, "output");
		}
		fsync(out);
	}

	/* Process the buffer for number of lines */
	for (p = buf; p != NULL && *p != '\0';)
		if ((p = strchr(p, '\n')) != NULL)
			dpv_overall_read++, p++, file->read++;

	/* Calculate percentage of completion (if possible) */
	if (file->length >= 0) {
		progress = (file->read * 100 / file->length);

		/* If no_overrun, do not return 100% until read >= length */
		if (no_overrun && progress == 100 && file->read < file->length)
			progress--;
			
		return (progress);
	} else
		return (-1);
}