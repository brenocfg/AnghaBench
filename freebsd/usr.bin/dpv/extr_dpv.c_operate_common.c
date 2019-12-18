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
struct stat {int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_mode; } ;
struct dpv_file_node {int path; void* status; } ;
typedef  int /*<<< orphan*/  blksize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE_MAX ; 
 scalar_t__ BUFSIZE_SMALL ; 
#define  DPV_OUTPUT_FILE 129 
#define  DPV_OUTPUT_SHELL 128 
 void* DPV_STATUS_FAILED ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPHYS ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PHYSPAGES_THRESHOLD ; 
 scalar_t__ STDIN_FILENO ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 scalar_t__ bsize ; 
 int /*<<< orphan*/ * buf ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fd ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ isatty (scalar_t__) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 scalar_t__ multiple ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int output_type ; 
 scalar_t__ realpath (int,char*) ; 
 char* rpath ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
operate_common(struct dpv_file_node *file, int out)
{
	struct stat sb;

	/* Open the file if necessary */
	if (fd < 0) {
		if (multiple) {
			/* Resolve the file path and attempt to open it */
			if (realpath(file->path, rpath) == 0 ||
			    (fd = open(rpath, O_RDONLY)) < 0) {
				warn("%s", file->path);
				file->status = DPV_STATUS_FAILED;
				return (-1);
			}
		} else {
			/* Assume stdin, but if that's a TTY instead use the
			 * highest numbered file descriptor (obtained by
			 * generating new fd and then decrementing).
			 *
			 * NB: /dev/stdin should always be open(2)'able
			 */
			fd = STDIN_FILENO;
			if (isatty(fd)) {
				fd = open("/dev/stdin", O_RDONLY);
				close(fd--);
			}

			/* This answer might be wrong, if dpv(3) has (by
			 * request) opened an output file or pipe. If we
			 * told dpv(3) to open a file, subtract one from
			 * previous answer. If instead we told dpv(3) to
			 * prepare a pipe output, subtract two.
			 */
			switch(output_type) {
			case DPV_OUTPUT_FILE:
				fd -= 1;
				break;
			case DPV_OUTPUT_SHELL:
				fd -= 2;
				break;
			}
		}
	}

	/* Allocate buffer if necessary */
	if (buf == NULL) {
		/* Use output block size as buffer size if available */
		if (out >= 0) {
			if (fstat(out, &sb) != 0) {
				warn("%i", out);
				file->status = DPV_STATUS_FAILED;
				return (-1);
			}
			if (S_ISREG(sb.st_mode)) {
				if (sysconf(_SC_PHYS_PAGES) >
				    PHYSPAGES_THRESHOLD)
					bsize = MIN(BUFSIZE_MAX, MAXPHYS * 8);
				else
					bsize = BUFSIZE_SMALL;
			} else
				bsize = MAX(sb.st_blksize,
				    (blksize_t)sysconf(_SC_PAGESIZE));
		} else
			bsize = MIN(BUFSIZE_MAX, MAXPHYS * 8);

		/* Attempt to allocate */
		if ((buf = malloc(bsize+1)) == NULL) {
			end_dialog();
			err(EXIT_FAILURE, "Out of memory?!");
		}
	}

	return (0);
}