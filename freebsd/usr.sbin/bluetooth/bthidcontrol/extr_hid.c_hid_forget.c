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
struct hid_device {int new_device; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int FAILED ; 
 int OK ; 
 int /*<<< orphan*/  clean_config () ; 
 struct hid_device* get_hid_device (int /*<<< orphan*/ *) ; 
 scalar_t__ read_config_file () ; 
 scalar_t__ read_hids_file () ; 
 scalar_t__ write_hids_file () ; 

__attribute__((used)) static int
hid_forget(bdaddr_t *bdaddr, int argc, char **argv)
{
	struct hid_device	*hd = NULL;
	int			 e = FAILED;

	if (read_config_file() == 0) {
		if (read_hids_file() == 0) {
			if ((hd = get_hid_device(bdaddr)) != NULL) {
				hd->new_device = 1;
				if (write_hids_file() == 0)
					e = OK;
			}
		}

		clean_config();
	}

	return (e);
}