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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct m_ext2fs {int e2fs_bsize; int /*<<< orphan*/  e2fs_csum_seed; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct ext2fs_extattr_header {int /*<<< orphan*/  h_checksum; } ;
typedef  int /*<<< orphan*/  facl ;

/* Variables and functions */
 int /*<<< orphan*/  calculate_crc32c (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
ext2_extattr_blk_csum(struct inode *ip, uint64_t facl,
    struct ext2fs_extattr_header *header)
{
	struct m_ext2fs *fs;
	uint32_t crc, old_crc;

	fs = ip->i_e2fs;

	old_crc = header->h_checksum;

	header->h_checksum = 0;
	crc = calculate_crc32c(fs->e2fs_csum_seed, (uint8_t *)&facl, sizeof(facl));
	crc = calculate_crc32c(crc, (uint8_t *)header, fs->e2fs_bsize);
	header->h_checksum = old_crc;

	return (crc);
}