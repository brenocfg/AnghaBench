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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct raid_map {int /*<<< orphan*/  data_encryption_key_index; int /*<<< orphan*/  volume_blk_size; } ;
struct pqi_enc_info {int encrypt_tweak_upper; int encrypt_tweak_lower; int /*<<< orphan*/  data_enc_key_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LE16 (int /*<<< orphan*/ *) ; 
 int GET_LE32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pqisrc_set_enc_info(
	struct pqi_enc_info *enc_info, struct raid_map *raid_map,
	uint64_t first_block)
{
	uint32_t volume_blk_size;

	/*
	 * Set the encryption tweak values based on logical block address.
	 * If the block size is 512, the tweak value is equal to the LBA.
	 * For other block sizes, tweak value is (LBA * block size) / 512.
	 */
	volume_blk_size = GET_LE32((uint8_t *)&raid_map->volume_blk_size);
	if (volume_blk_size != 512)
		first_block = (first_block * volume_blk_size) / 512;

	enc_info->data_enc_key_index =
		GET_LE16((uint8_t *)&raid_map->data_encryption_key_index);
	enc_info->encrypt_tweak_upper = ((uint32_t)(((first_block) >> 16) >> 16));
	enc_info->encrypt_tweak_lower = ((uint32_t)(first_block));
}