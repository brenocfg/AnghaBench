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
struct mfi_info_component {char* name; char* version; int /*<<< orphan*/  build_time; int /*<<< orphan*/  build_date; } ;

/* Variables and functions */
 char* fw_date_width ; 
 char* fw_name_width ; 
 int /*<<< orphan*/  fw_time_width ; 
 char* fw_version_width ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void
display_firmware(struct mfi_info_component *comp, const char *tag)
{

	printf("%-*s  %-*s  %-*s  %-*s  %s\n", fw_name_width, comp->name,
	    fw_version_width, comp->version, fw_date_width, comp->build_date,
	    fw_time_width, comp->build_time, tag);
}