#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ stored_crc32; scalar_t__ has_blake2; int /*<<< orphan*/  b2state; int /*<<< orphan*/  calculated_crc32; } ;
struct rar5 {TYPE_1__ file; scalar_t__ skip_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  blake2sp_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void update_crc(struct rar5* rar, const uint8_t* p, size_t to_read) {
    int verify_crc;

	if(rar->skip_mode) {
#if defined CHECK_CRC_ON_SOLID_SKIP
		verify_crc = 1;
#else
		verify_crc = 0;
#endif
	} else
		verify_crc = 1;

	if(verify_crc) {
		/* Don't update CRC32 if the file doesn't have the
		 * `stored_crc32` info filled in. */
		if(rar->file.stored_crc32 > 0) {
			rar->file.calculated_crc32 =
				crc32(rar->file.calculated_crc32, p, to_read);
		}

		/* Check if the file uses an optional BLAKE2sp checksum
		 * algorithm. */
		if(rar->file.has_blake2 > 0) {
			/* Return value of the `update` function is always 0,
			 * so we can explicitly ignore it here. */
			(void) blake2sp_update(&rar->file.b2state, p, to_read);
		}
	}
}