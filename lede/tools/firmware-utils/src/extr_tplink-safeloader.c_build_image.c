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
typedef  int /*<<< orphan*/  uint32_t ;
struct stat {scalar_t__ st_size; } ;
struct image_partition_entry {scalar_t__ name; } ;
struct flash_partition_entry {char* name; scalar_t__ size; scalar_t__ base; } ;
struct device_info {int /*<<< orphan*/  id; scalar_t__ soft_ver; struct flash_partition_entry* partitions; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int MAX_PARTITIONS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_image_partition (struct image_partition_entry) ; 
 int fwrite (void*,size_t,int,int /*<<< orphan*/ *) ; 
 void* generate_factory_image (struct device_info*,struct image_partition_entry*,size_t*) ; 
 void* generate_sysupgrade_image (struct device_info*,struct image_partition_entry*,size_t*) ; 
 struct image_partition_entry make_partition_table (struct flash_partition_entry*) ; 
 struct image_partition_entry make_soft_version (int /*<<< orphan*/ ) ; 
 struct image_partition_entry make_soft_version_from_string (scalar_t__) ; 
 struct image_partition_entry make_support_list (struct device_info*) ; 
 struct image_partition_entry put_data (char*,char const*,int) ; 
 struct image_partition_entry read_file (char*,char const*,int,struct flash_partition_entry*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void build_image(const char *output,
		const char *kernel_image,
		const char *rootfs_image,
		uint32_t rev,
		bool add_jffs2_eof,
		bool sysupgrade,
		struct device_info *info) {

	size_t i;

	struct image_partition_entry parts[7] = {};

	struct flash_partition_entry *firmware_partition = NULL;
	struct flash_partition_entry *os_image_partition = NULL;
	struct flash_partition_entry *file_system_partition = NULL;
	size_t firmware_partition_index = 0;

	for (i = 0; info->partitions[i].name; i++) {
		if (!strcmp(info->partitions[i].name, "firmware"))
		{
			firmware_partition = &info->partitions[i];
			firmware_partition_index = i;
		}
	}

	if (firmware_partition)
	{
		os_image_partition = &info->partitions[firmware_partition_index];
		file_system_partition = &info->partitions[firmware_partition_index + 1];

		struct stat kernel;
		if (stat(kernel_image, &kernel) < 0)
			error(1, errno, "unable to stat file `%s'", kernel_image);

		if (kernel.st_size > firmware_partition->size)
			error(1, 0, "kernel overflowed firmware partition\n");

		for (i = MAX_PARTITIONS-1; i >= firmware_partition_index + 1; i--)
			info->partitions[i+1] = info->partitions[i];

		file_system_partition->name = "file-system";
		file_system_partition->base = firmware_partition->base + kernel.st_size;

		/* Align partition start to erase blocks for factory images only */
		if (!sysupgrade)
			file_system_partition->base = ALIGN(firmware_partition->base + kernel.st_size, 0x10000);

		file_system_partition->size = firmware_partition->size - file_system_partition->base;

		os_image_partition->name = "os-image";
		os_image_partition->size = kernel.st_size;
	}

	parts[0] = make_partition_table(info->partitions);
	if (info->soft_ver)
		parts[1] = make_soft_version_from_string(info->soft_ver);
	else
		parts[1] = make_soft_version(rev);

	parts[2] = make_support_list(info);
	parts[3] = read_file("os-image", kernel_image, false, NULL);
	parts[4] = read_file("file-system", rootfs_image, add_jffs2_eof, file_system_partition);

	/* Some devices need the extra-para partition to accept the firmware */
	if (strcasecmp(info->id, "ARCHER-C25-V1") == 0 ||
	    strcasecmp(info->id, "ARCHER-C59-V2") == 0 ||
	    strcasecmp(info->id, "ARCHER-C60-V2") == 0 ||
	    strcasecmp(info->id, "TLWR1043NV5") == 0) {
		const char mdat[11] = {0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
		parts[5] = put_data("extra-para", mdat, 11);
	} else if (strcasecmp(info->id, "ARCHER-A7-V5") == 0 || strcasecmp(info->id, "ARCHER-C7-V4") == 0 || strcasecmp(info->id, "ARCHER-C7-V5") == 0) {
		const char mdat[11] = {0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0xca, 0x00, 0x01, 0x00, 0x00};
		parts[5] = put_data("extra-para", mdat, 11);
	} else if (strcasecmp(info->id, "ARCHER-C6-V2") == 0) {
		const char mdat[11] = {0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};
		parts[5] = put_data("extra-para", mdat, 11);
	}

	size_t len;
	void *image;
	if (sysupgrade)
		image = generate_sysupgrade_image(info, parts, &len);
	else
		image = generate_factory_image(info, parts, &len);

	FILE *file = fopen(output, "wb");
	if (!file)
		error(1, errno, "unable to open output file");

	if (fwrite(image, len, 1, file) != 1)
		error(1, 0, "unable to write output file");

	fclose(file);

	free(image);

	for (i = 0; parts[i].name; i++)
		free_image_partition(parts[i]);
}