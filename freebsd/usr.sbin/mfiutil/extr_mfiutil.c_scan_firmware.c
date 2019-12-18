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
struct mfi_info_component {int /*<<< orphan*/  build_time; int /*<<< orphan*/  build_date; int /*<<< orphan*/  version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int fw_date_width ; 
 int fw_name_width ; 
 int fw_time_width ; 
 int fw_version_width ; 
 int strlen (int /*<<< orphan*/ ) ; 

void
scan_firmware(struct mfi_info_component *comp)
{
	int len;

	len = strlen(comp->name);
	if (fw_name_width < len)
		fw_name_width = len;
	len = strlen(comp->version);
	if (fw_version_width < len)
		fw_version_width = len;
	len = strlen(comp->build_date);
	if (fw_date_width < len)
		fw_date_width = len;
	len = strlen(comp->build_time);
	if (fw_time_width < len)
		fw_time_width = len;
}