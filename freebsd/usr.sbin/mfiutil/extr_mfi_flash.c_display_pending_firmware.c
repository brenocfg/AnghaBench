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
typedef  size_t u_int ;
struct mfi_info_component {int /*<<< orphan*/  build_time; int /*<<< orphan*/  build_date; int /*<<< orphan*/  version; int /*<<< orphan*/  name; } ;
struct mfi_ctrl_info {int pending_image_component_count; struct mfi_info_component* pending_image_component; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_firmware (struct mfi_info_component*,char*) ; 
 int errno ; 
 scalar_t__ mfi_ctrl_get_info (int,struct mfi_ctrl_info*,int /*<<< orphan*/ *) ; 
 int mfi_unit ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  scan_firmware (struct mfi_info_component*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
display_pending_firmware(int fd)
{
	struct mfi_ctrl_info info;
	struct mfi_info_component header;
	int error;
	u_int i;

	if (mfi_ctrl_get_info(fd, &info, NULL) < 0) {
		error = errno;
		warn("Failed to get controller info");
		return (error);
	}

	printf("mfi%d Pending Firmware Images:\n", mfi_unit);
	strcpy(header.name, "Name");
	strcpy(header.version, "Version");
	strcpy(header.build_date, "Date");
	strcpy(header.build_time, "Time");
	scan_firmware(&header);
	if (info.pending_image_component_count > 8)
		info.pending_image_component_count = 8;
	for (i = 0; i < info.pending_image_component_count; i++)
		scan_firmware(&info.pending_image_component[i]);
	display_firmware(&header, "");
	for (i = 0; i < info.pending_image_component_count; i++)
		display_firmware(&info.pending_image_component[i], "");

	return (0);
}