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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDR_OFF_CHECKSUM ; 
 int /*<<< orphan*/  crc32_accumulate_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crc32_csum(uint8_t *buf, const size_t len)
{
	uint32_t crc;
	size_t i;

	crc = ~0;
	for (i = 0; i < len; i += 4) {
		crc = crc32_accumulate_8(crc, buf[i + 3]);
		crc = crc32_accumulate_8(crc, buf[i + 2]);
		crc = crc32_accumulate_8(crc, buf[i + 1]);
		crc = crc32_accumulate_8(crc, buf[i]);
	}
	crc = ~crc;

	writel(buf, HDR_OFF_CHECKSUM, crc);
}