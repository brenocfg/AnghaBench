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
struct fwimage_trailer {int /*<<< orphan*/  crc32; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FWIMAGE_MAGIC ; 
 int add_metadata (struct fwimage_trailer*) ; 
 int add_signature (struct fwimage_trailer*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_file ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ metadata_file ; 
 int /*<<< orphan*/  msg (char*) ; 
 scalar_t__ signature_file ; 
 int /*<<< orphan*/  trailer_update_crc (struct fwimage_trailer*,char*,int) ; 

__attribute__((used)) static int
add_data(const char *name)
{
	struct fwimage_trailer tr = {
		.magic = cpu_to_be32(FWIMAGE_MAGIC),
		.crc32 = ~0,
	};
	int file_len = 0;
	int ret = 0;

	firmware_file = fopen(name, "r+");
	if (!firmware_file) {
		msg("Failed to open firmware file\n");
		return 1;
	}

	while (1) {
		char buf[512];
		int len;

		len = fread(buf, 1, sizeof(buf), firmware_file);
		if (!len)
			break;

		file_len += len;
		trailer_update_crc(&tr, buf, len);
	}

	if (metadata_file)
		ret = add_metadata(&tr);
	else if (signature_file)
		ret = add_signature(&tr);

	if (ret) {
		fflush(firmware_file);
		ftruncate(fileno(firmware_file), file_len);
	}

	return ret;
}