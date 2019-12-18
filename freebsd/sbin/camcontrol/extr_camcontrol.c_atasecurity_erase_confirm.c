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
struct cam_device {char* device_name; char* dev_unit_num; int /*<<< orphan*/  given_unit_number; int /*<<< orphan*/  given_dev_name; } ;
struct ata_params {int dummy; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
atasecurity_erase_confirm(struct cam_device *device,
			  struct ata_params* ident_buf)
{

	printf("\nYou are about to ERASE ALL DATA from the following"
	       " device:\n%s%d,%s%d: ", device->device_name,
	       device->dev_unit_num, device->given_dev_name,
	       device->given_unit_number);
	ata_print_ident(ident_buf);

	for(;;) {
		char str[50];
		printf("\nAre you SURE you want to ERASE ALL DATA? (yes/no) ");

		if (fgets(str, sizeof(str), stdin) != NULL) {
			if (strncasecmp(str, "yes", 3) == 0) {
				return (1);
			} else if (strncasecmp(str, "no", 2) == 0) {
				return (0);
			} else {
				printf("Please answer \"yes\" or "
				       "\"no\"\n");
			}
		}
	}

	/* NOTREACHED */
	return (0);
}