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

/* Variables and functions */
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  SERIAL_GETNAME ; 
 int adapter_type ; 
 char* chan_name ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char**) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
open_chan_ctl (int num)
{
	char device [80];
	int fd;

#ifdef __linux__
	sprintf (device, "/dev/serial/ctl%d", num);
#else
	switch (adapter_type) {
	case 0:
		sprintf (device, "/dev/cx%d", num);
		break;
	case 1:
		sprintf (device, "/dev/ct%d", num);
		break;
	case 2:
		sprintf (device, "/dev/cp%d", num);
		break;
	case 3:
		sprintf (device, "/dev/ce%d", num);
		break;
	}
#endif
	fd = open (device, 0);
	if (fd < 0) {
		if (errno == ENODEV)
			fprintf (stderr, "chan%d: not configured\n", num);
		else
			perror (device);
		exit (-1);
	}
#ifdef __linux__
	if (ioctl (fd, SERIAL_GETNAME, &chan_name) < 0)
		sprintf (chan_name, "chan%d", num);
#else
	switch (adapter_type) {
	case 0: sprintf (chan_name, "cx%d", num); break;
	case 1: sprintf (chan_name, "ct%d", num); break;
	case 2: sprintf (chan_name, "cp%d", num); break;
	case 3: sprintf (chan_name, "ce%d", num); break;
	}
#endif
	return fd;
}