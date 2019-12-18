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
typedef  int /*<<< orphan*/  u_int64_t ;
struct cam_device {int /*<<< orphan*/  given_unit_number; int /*<<< orphan*/  given_dev_name; int /*<<< orphan*/  dev_unit_num; int /*<<< orphan*/  device_name; } ;
struct ata_params {int dummy; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
atahpa_set_confirm(struct cam_device *device, struct ata_params* ident_buf,
		   u_int64_t maxsize, int persist)
{
	printf("\nYou are about to configure HPA to limit the user accessible\n"
	       "sectors to %ju %s on the device:\n%s%d,%s%d: ", maxsize,
	       persist ? "persistently" : "temporarily",
	       device->device_name, device->dev_unit_num,
	       device->given_dev_name, device->given_unit_number);
	ata_print_ident(ident_buf);

	for(;;) {
		char str[50];
		printf("\nAre you SURE you want to configure HPA? (yes/no) ");

		if (NULL != fgets(str, sizeof(str), stdin)) {
			if (0 == strncasecmp(str, "yes", 3)) {
				return (1);
			} else if (0 == strncasecmp(str, "no", 2)) {
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