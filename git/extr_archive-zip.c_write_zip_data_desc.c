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
struct zip_data_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  crc32; int /*<<< orphan*/  magic; } ;
struct zip64_data_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  crc32; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 scalar_t__ ZIP64_DATA_DESC_SIZE ; 
 scalar_t__ ZIP_DATA_DESC_SIZE ; 
 int /*<<< orphan*/  copy_le32 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  copy_le64 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_or_die (int,struct zip_data_desc*,scalar_t__) ; 
 int /*<<< orphan*/  zip_offset ; 

__attribute__((used)) static void write_zip_data_desc(unsigned long size,
				unsigned long compressed_size,
				unsigned long crc)
{
	if (size >= 0xffffffff || compressed_size >= 0xffffffff) {
		struct zip64_data_desc trailer;
		copy_le32(trailer.magic, 0x08074b50);
		copy_le32(trailer.crc32, crc);
		copy_le64(trailer.compressed_size, compressed_size);
		copy_le64(trailer.size, size);
		write_or_die(1, &trailer, ZIP64_DATA_DESC_SIZE);
		zip_offset += ZIP64_DATA_DESC_SIZE;
	} else {
		struct zip_data_desc trailer;
		copy_le32(trailer.magic, 0x08074b50);
		copy_le32(trailer.crc32, crc);
		copy_le32(trailer.compressed_size, compressed_size);
		copy_le32(trailer.size, size);
		write_or_die(1, &trailer, ZIP_DATA_DESC_SIZE);
		zip_offset += ZIP_DATA_DESC_SIZE;
	}
}