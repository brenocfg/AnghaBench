#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone_args ;
typedef  int uint32_t ;
struct TYPE_3__ {int zone_mode; } ;
struct TYPE_4__ {TYPE_1__ disk_params; } ;
struct disk_zone_args {TYPE_2__ zone_params; int /*<<< orphan*/  zone_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCZONECMD ; 
 int /*<<< orphan*/  DISK_ZONE_GET_PARAMS ; 
#define  DISK_ZONE_MODE_DRIVE_MANAGED 131 
#define  DISK_ZONE_MODE_HOST_AWARE 130 
#define  DISK_ZONE_MODE_HOST_MANAGED 129 
#define  DISK_ZONE_MODE_NONE 128 
 int /*<<< orphan*/  bzero (struct disk_zone_args*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct disk_zone_args*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int
zonecheck(int fd, uint32_t *zone_mode, char *zone_str, size_t zone_str_len)
{
	struct disk_zone_args zone_args;
	int error;

	bzero(&zone_args, sizeof(zone_args));

	zone_args.zone_cmd = DISK_ZONE_GET_PARAMS;
	error = ioctl(fd, DIOCZONECMD, &zone_args);

	if (error == 0) {
		*zone_mode = zone_args.zone_params.disk_params.zone_mode;

		switch (*zone_mode) {
		case DISK_ZONE_MODE_NONE:
			snprintf(zone_str, zone_str_len, "Not_Zoned");
			break;
		case DISK_ZONE_MODE_HOST_AWARE:
			snprintf(zone_str, zone_str_len, "Host_Aware");
			break;
		case DISK_ZONE_MODE_DRIVE_MANAGED:
			snprintf(zone_str, zone_str_len, "Drive_Managed");
			break;
		case DISK_ZONE_MODE_HOST_MANAGED:
			snprintf(zone_str, zone_str_len, "Host_Managed");
			break;
		default:
			snprintf(zone_str, zone_str_len, "Unknown_zone_mode_%u",
			    *zone_mode);
			break;
		}
	}
	return (error);
}