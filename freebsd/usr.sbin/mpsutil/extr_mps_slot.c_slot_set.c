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
typedef  unsigned long U32 ;
typedef  long U16 ;

/* Variables and functions */
 int EINVAL ; 
 long UINT16_MAX ; 
 unsigned long UINT32_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int mps_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mps_set_slot_status (int,long,long,unsigned long) ; 
 int /*<<< orphan*/  mps_unit ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
slot_set(int argc, char **argv)
{
	char *endptr;
	unsigned long ux;
	long x;
	int error;
	int fd;
	U32 status;
	U16 handle;
	U16 slot;

	if (argc != 5) {
		warnx("Incorrect number of arguments");
		return (EINVAL);
	}

	if (strcmp(argv[1], "status") != 0) {
		warnx("Invalid argument '%s', expecting 'status'",
		    argv[1]);
		return (EINVAL);
	}

	errno = 0;
	x = strtol(argv[2], &endptr, 0);
	if (*endptr != '\0' || errno != 0 || x < 0 || x > UINT16_MAX) {
		warnx("Invalid enclosure handle argument '%s'", argv[2]);
		return (EINVAL);
	}
	handle = x;

	errno = 0;
	x = strtol(argv[3], &endptr, 0);
	if (*endptr != '\0' || errno != 0 || x < 0 || x > UINT16_MAX) {
		warnx("Invalid slot argument '%s'", argv[3]);
		return (EINVAL);
	}
	slot = x;

	errno = 0;
	ux = strtoul(argv[4], &endptr, 0);
	if (*endptr != '\0' || errno != 0 || ux > UINT32_MAX) {
		warnx("Invalid status argument '%s'", argv[4]);
		return (EINVAL);
	}
	status = ux;

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		return (error);
	}

	if (mps_set_slot_status(fd, handle, slot, status) != 0) {
		warnx("Failed to set status");
		close(fd);
		return (1);
	}

	close(fd);
	printf("Successfully set slot status\n");
	return (0);
}