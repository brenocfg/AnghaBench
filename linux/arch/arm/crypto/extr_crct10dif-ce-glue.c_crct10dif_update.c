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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 unsigned int CRC_T10DIF_PMULL_CHUNK_SIZE ; 
 int /*<<< orphan*/  crc_t10dif_generic (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crc_t10dif_pmull (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/ * shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crct10dif_update(struct shash_desc *desc, const u8 *data,
			    unsigned int length)
{
	u16 *crc = shash_desc_ctx(desc);

	if (length >= CRC_T10DIF_PMULL_CHUNK_SIZE && crypto_simd_usable()) {
		kernel_neon_begin();
		*crc = crc_t10dif_pmull(*crc, data, length);
		kernel_neon_end();
	} else {
		*crc = crc_t10dif_generic(*crc, data, length);
	}

	return 0;
}