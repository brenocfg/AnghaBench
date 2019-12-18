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
typedef  int u8 ;
struct e752x_error_info {int hi_ferr; int hi_nerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hub_error (int,int,int*,int) ; 

__attribute__((used)) static void e752x_check_hub_interface(struct e752x_error_info *info,
				int *error_found, int handle_error)
{
	u8 stat8;

	//pci_read_config_byte(dev,E752X_HI_FERR,&stat8);

	stat8 = info->hi_ferr;

	if (stat8 & 0x7f) {	/* Error, so process */
		stat8 &= 0x7f;

		if (stat8 & 0x2b)
			hub_error(1, stat8 & 0x2b, error_found, handle_error);

		if (stat8 & 0x54)
			hub_error(0, stat8 & 0x54, error_found, handle_error);
	}
	//pci_read_config_byte(dev,E752X_HI_NERR,&stat8);

	stat8 = info->hi_nerr;

	if (stat8 & 0x7f) {	/* Error, so process */
		stat8 &= 0x7f;

		if (stat8 & 0x2b)
			hub_error(1, stat8 & 0x2b, error_found, handle_error);

		if (stat8 & 0x54)
			hub_error(0, stat8 & 0x54, error_found, handle_error);
	}
}