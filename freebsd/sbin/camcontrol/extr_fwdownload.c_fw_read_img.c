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
struct stat {int st_size; } ;
struct fw_vendor {int type; int /*<<< orphan*/  dev_type; } ;
struct cam_device {int dummy; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  T_SEQUENTIAL ; 
#define  VENDOR_IBM 130 
#define  VENDOR_QUALSTAR 129 
#define  VENDOR_SEAGATE 128 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  fw_validate_ibm (struct cam_device*,int,int,int,char*,char const*,int) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static char *
fw_read_img(struct cam_device *dev, int retry_count, int timeout, int quiet,
	    const char *fw_img_path, struct fw_vendor *vp, int *num_bytes)
{
	int fd;
	struct stat stbuf;
	char *buf;
	off_t img_size;
	int skip_bytes = 0;

	if ((fd = open(fw_img_path, O_RDONLY)) < 0) {
		warn("Could not open image file %s", fw_img_path);
		return (NULL);
	}
	if (fstat(fd, &stbuf) < 0) {
		warn("Could not stat image file %s", fw_img_path);
		goto bailout1;
	}
	if ((img_size = stbuf.st_size) == 0) {
		warnx("Zero length image file %s", fw_img_path);
		goto bailout1;
	}
	if ((buf = malloc(img_size)) == NULL) {
		warnx("Could not allocate buffer to read image file %s",
		    fw_img_path);
		goto bailout1;
	}
	/* Skip headers if applicable. */
	switch (vp->type) {
	case VENDOR_SEAGATE:
		if (read(fd, buf, 16) != 16) {
			warn("Could not read image file %s", fw_img_path);
			goto bailout;
		}
		if (lseek(fd, 0, SEEK_SET) == -1) {
			warn("Unable to lseek");
			goto bailout;
		}
		if ((strncmp(buf, "SEAGATE,SEAGATE ", 16) == 0) ||
		    (img_size % 512 == 80))
			skip_bytes = 80;
		break;
	case VENDOR_QUALSTAR:
		skip_bytes = img_size % 1030;
		break;
	case VENDOR_IBM: {
		if (vp->dev_type != T_SEQUENTIAL)
			break;
		if (fw_validate_ibm(dev, retry_count, timeout, fd, buf,
				    fw_img_path, quiet) != 0)
			goto bailout;
		break;
	}
	default:
		break;
	}
	if (skip_bytes != 0) {
		fprintf(stdout, "Skipping %d byte header.\n", skip_bytes);
		if (lseek(fd, skip_bytes, SEEK_SET) == -1) {
			warn("Could not lseek");
			goto bailout;
		}
		img_size -= skip_bytes;
	}
	/* Read image into a buffer. */
	if (read(fd, buf, img_size) != img_size) {
		warn("Could not read image file %s", fw_img_path);
		goto bailout;
	}
	*num_bytes = img_size;
	close(fd);
	return (buf);
bailout:
	free(buf);
bailout1:
	close(fd);
	*num_bytes = 0;
	return (NULL);
}