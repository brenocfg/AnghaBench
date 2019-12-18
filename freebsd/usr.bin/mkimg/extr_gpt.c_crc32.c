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
typedef  int uint32_t ;

/* Variables and functions */
 int* crc32_tab ; 

__attribute__((used)) static uint32_t
crc32(const void *buf, size_t sz)
{
	const uint8_t *p = (const uint8_t *)buf;
	uint32_t crc = ~0U;

	while (sz--)
		crc = crc32_tab[(crc ^ *p++) & 0xff] ^ (crc >> 8);
	return (crc ^ ~0U);
}