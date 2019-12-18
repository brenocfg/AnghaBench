#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* devname; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ devid_nmlist_t ;
typedef  int /*<<< orphan*/  ddi_devid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVID_MINOR_NAME_ALL ; 
 int O_NDELAY ; 
 int O_RDONLY ; 
 scalar_t__ devid_deviceid_to_nmlist (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  devid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devid_free_nmlist (TYPE_1__*) ; 
 scalar_t__ devid_get (int,int /*<<< orphan*/ *) ; 
 scalar_t__ devid_get_minor_name (int,char**) ; 
 char* devid_str_encode (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devid_str_free (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

int
main(int argc, char *argv[])
{
	int		fd;
	ddi_devid_t	devid;
	char		*minor_name, *devidstr, *device;
#ifdef DEBUG
	devid_nmlist_t  *list = NULL;
	char		*search_path;
	int		i;
#endif

	if (argc == 1) {
		(void) printf("%s <devicepath> [search path]\n",
		    argv[0]);
		exit(1);
	}
	device = argv[1];

	if ((fd = open(device, O_RDONLY|O_NDELAY)) < 0) {
		perror(device);
		exit(1);
	}
	if (devid_get(fd, &devid) != 0) {
		perror("devid_get");
		exit(1);
	}
	if (devid_get_minor_name(fd, &minor_name) != 0) {
		perror("devid_get_minor_name");
		exit(1);
	}
	if ((devidstr = devid_str_encode(devid, minor_name)) == 0) {
		perror("devid_str_encode");
		exit(1);
	}

	(void) printf("devid %s\n", devidstr);

	devid_str_free(devidstr);

#ifdef DEBUG
	if (argc == 3) {
		search_path = argv[2];
	} else {
		search_path = "/dev/";
	}

	if (devid_deviceid_to_nmlist(search_path, devid, DEVID_MINOR_NAME_ALL,
	    &list)) {
		perror("devid_deviceid_to_nmlist");
		exit(1);
	}

	/* loop through list and process device names and numbers */
	for (i = 0; list[i].devname != NULL; i++) {
		(void) printf("devname: %s %p\n", list[i].devname, list[i].dev);
	}
	devid_free_nmlist(list);

#endif /* DEBUG */

	devid_str_free(minor_name);
	devid_free(devid);

	return (0);
}