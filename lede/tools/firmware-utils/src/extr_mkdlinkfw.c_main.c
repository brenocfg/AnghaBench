#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* file_name; } ;
struct TYPE_7__ {void* file_name; } ;
struct TYPE_6__ {void* file_name; } ;
struct TYPE_5__ {void* file_name; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 scalar_t__ FACTORY ; 
 scalar_t__ SYSUPGRADE ; 
 int /*<<< orphan*/  basename (char*) ; 
 int build_fw () ; 
 int check_options () ; 
 scalar_t__ family_member ; 
 scalar_t__ firmware_size ; 
 int getopt (int,char**,char*) ; 
 TYPE_4__ image_info ; 
 scalar_t__ image_type ; 
 int inspect_fw () ; 
 TYPE_3__ inspect_info ; 
 TYPE_2__ kernel_info ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 void* ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  rom_id ; 
 TYPE_1__ rootfs_info ; 
 int /*<<< orphan*/  sscanf (void*,char*,scalar_t__*) ; 
 int strlen (void*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int wrap_fw () ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;

	progname = basename(argv[0]);
	image_type = SYSUPGRADE;
	family_member = 0;
	firmware_size = 0;

	while (1) {
		int c;

		c = getopt(argc, argv, "f:F:i:hk:m:o:r:s:");
		if (c == -1)
			break;

		switch (c) {
		case 'f':
			sscanf(optarg, "0x%hx", &family_member);
			break;
		case 'F':
			image_info.file_name = optarg;
			image_type = FACTORY;
			break;
		case 'i':
			inspect_info.file_name = optarg;
			break;
		case 'k':
			kernel_info.file_name = optarg;
			break;
		case 'm':
			if (strlen(optarg) == 12)
				memcpy(rom_id, optarg, 12);
			break;
		case 'r':
			rootfs_info.file_name = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 's':
			sscanf(optarg, "0x%x", &firmware_size);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	ret = check_options();
	if (ret)
		goto out;

	if (!inspect_info.file_name) {
		if (image_type == FACTORY)
			ret = wrap_fw();
		else
			ret = build_fw();
		}
	else
		ret = inspect_fw();

 out:
	return ret;

}