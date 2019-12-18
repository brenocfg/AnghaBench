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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cpath ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  SPIGENIOC_GET_CLOCK_SPEED ; 
 int /*<<< orphan*/  SPIGENIOC_GET_SPI_MODE ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  realpath (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
get_info(int hdev, const char *dev_name)
{
	uint32_t fmode, fspeed;
	int err;
	char temp_buf[PATH_MAX], cpath[PATH_MAX];

	if (!realpath(dev_name, cpath)) /* get canonical name for info purposes */
		strlcpy(cpath, temp_buf, sizeof(cpath));  /* this shouldn't happen */

	err = ioctl(hdev, SPIGENIOC_GET_SPI_MODE, &fmode);

	if (err == 0)
		err = ioctl(hdev, SPIGENIOC_GET_CLOCK_SPEED, &fspeed);

	if (err == 0) {
		fprintf(stderr,
		        "Device name:   %s\n"
		        "Device mode:   %d\n"
		        "Device speed:  %d\n",
		        cpath, fmode, fspeed);//, max_cmd, max_data, temp_buf);
	}
	else
		fprintf(stderr, "Unable to query info (err=%d), errno=%d\n",
		    err, errno);

	return err;
}