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
struct hid_device {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int FAILED ; 
 int OK ; 
 int /*<<< orphan*/  clean_config () ; 
 struct hid_device* get_hid_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dump_descriptor (int /*<<< orphan*/ ) ; 
 scalar_t__ read_config_file () ; 

__attribute__((used)) static int
hid_dump(bdaddr_t *bdaddr, int argc, char **argv)
{
	struct hid_device	*hd = NULL;
	int			 e = FAILED;

	if (read_config_file() == 0) {
		if ((hd = get_hid_device(bdaddr)) != NULL) {
			hid_dump_descriptor(hd->desc);
			e = OK;
		} 

		clean_config();
	}

	return (e);
}