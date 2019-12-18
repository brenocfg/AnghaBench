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
typedef  int /*<<< orphan*/  dev_file ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,char const*,int,...) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  IB_USER_MAD_ENABLE_PKEY ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TRACE (char*,char const*,int) ; 
 char* UMAD_DEV_DIR ; 
 int UMAD_DEV_FILE_SZ ; 
 int abi_version ; 
 int dev_to_umad_id (char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int new_user_mad_api ; 
 int open (char*,int) ; 
 char* resolve_ca_name (char const*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int umad_open_port(const char *ca_name, int portnum)
{
	char dev_file[UMAD_DEV_FILE_SZ];
	int umad_id, fd;

	TRACE("ca %s port %d", ca_name, portnum);

	if (!(ca_name = resolve_ca_name(ca_name, &portnum)))
		return -ENODEV;

	DEBUG("opening %s port %d", ca_name, portnum);

	if ((umad_id = dev_to_umad_id(ca_name, portnum)) < 0)
		return -EINVAL;

	snprintf(dev_file, sizeof(dev_file), "%s/umad%d",
		 UMAD_DEV_DIR, umad_id);

	if ((fd = open(dev_file, O_RDWR | O_NONBLOCK)) < 0) {
		DEBUG("open %s failed: %s", dev_file, strerror(errno));
		return -EIO;
	}

	if (abi_version > 5 || !ioctl(fd, IB_USER_MAD_ENABLE_PKEY, NULL))
		new_user_mad_api = 1;
	else
		new_user_mad_api = 0;

	DEBUG("opened %s fd %d portid %d", dev_file, fd, umad_id);
	return fd;
}