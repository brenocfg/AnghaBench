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
struct iso9660 {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 size_t DR_length_offset ; 
 size_t SVD_file_structure_version_offset ; 
 int SVD_logical_block_size_offset ; 
 int /*<<< orphan*/  SVD_reserved1_offset ; 
 int /*<<< orphan*/  SVD_reserved1_size ; 
 int /*<<< orphan*/  SVD_reserved2_offset ; 
 int /*<<< orphan*/  SVD_reserved2_size ; 
 int /*<<< orphan*/  SVD_reserved3_offset ; 
 int /*<<< orphan*/  SVD_reserved3_size ; 
 int SVD_root_directory_record_offset ; 
 int SVD_type_L_path_table_offset ; 
 int SVD_type_M_path_table_offset ; 
 size_t SVD_type_offset ; 
 int SVD_volume_space_size_offset ; 
 scalar_t__ SYSTEM_AREA_BLOCK ; 
 scalar_t__ archive_be32dec (unsigned char const*) ; 
 scalar_t__ archive_le16dec (unsigned char const*) ; 
 scalar_t__ archive_le32dec (unsigned char const*) ; 
 int /*<<< orphan*/  isNull (struct iso9660*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isSVD(struct iso9660 *iso9660, const unsigned char *h)
{
	const unsigned char *p;
	ssize_t logical_block_size;
	int32_t volume_block;
	int32_t location;

	(void)iso9660; /* UNUSED */

	/* Type 2 means it's a SVD. */
	if (h[SVD_type_offset] != 2)
		return (0);

	/* Reserved field must be 0. */
	if (!isNull(iso9660, h, SVD_reserved1_offset, SVD_reserved1_size))
		return (0);
	if (!isNull(iso9660, h, SVD_reserved2_offset, SVD_reserved2_size))
		return (0);
	if (!isNull(iso9660, h, SVD_reserved3_offset, SVD_reserved3_size))
		return (0);

	/* File structure version must be 1 for ISO9660/ECMA119. */
	if (h[SVD_file_structure_version_offset] != 1)
		return (0);

	logical_block_size =
	    archive_le16dec(h + SVD_logical_block_size_offset);
	if (logical_block_size <= 0)
		return (0);

	volume_block = archive_le32dec(h + SVD_volume_space_size_offset);
	if (volume_block <= SYSTEM_AREA_BLOCK+4)
		return (0);

	/* Location of Occurrence of Type L Path Table must be
	 * available location,
	 * >= SYSTEM_AREA_BLOCK(16) + 2 and < Volume Space Size. */
	location = archive_le32dec(h+SVD_type_L_path_table_offset);
	if (location < SYSTEM_AREA_BLOCK+2 || location >= volume_block)
		return (0);

	/* The Type M Path Table must be at a valid location (WinISO
	 * and probably other programs omit this, so we allow zero)
	 *
	 * >= SYSTEM_AREA_BLOCK(16) + 2 and < Volume Space Size. */
	location = archive_be32dec(h+SVD_type_M_path_table_offset);
	if ((location > 0 && location < SYSTEM_AREA_BLOCK+2)
	    || location >= volume_block)
		return (0);

	/* Read Root Directory Record in Volume Descriptor. */
	p = h + SVD_root_directory_record_offset;
	if (p[DR_length_offset] != 34)
		return (0);

	return (48);
}