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
struct iiccmd {int dummy; } ;

/* Variables and functions */
 int EX_IOERR ; 
 int EX_NOINPUT ; 
 int EX_OK ; 
 int /*<<< orphan*/  I2CRSTCARD ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iiccmd*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reset_bus(struct iiccmd cmd, char *dev)
{
	int fd, error;

	fd = open(dev, O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "Error opening I2C controller (%s) for "
		    "resetting: %s\n", dev, strerror(errno));
		return (EX_NOINPUT);
	}

	printf("Resetting I2C controller on %s: ", dev);
	error = ioctl(fd, I2CRSTCARD, &cmd);
	close (fd);

	if (error) {
		printf("error: %s\n", strerror(errno));
		return (EX_IOERR);
	} else {
		printf("OK\n");
		return (EX_OK);
	}
}