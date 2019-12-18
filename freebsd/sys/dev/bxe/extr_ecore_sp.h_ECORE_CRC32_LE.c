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
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_crc32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline uint32_t
ECORE_CRC32_LE(uint32_t seed, uint8_t *mac, uint32_t len)
{
    uint32_t packet_buf[2] = {0};
    memcpy(((uint8_t *)(&packet_buf[0]))+2, &mac[0], 2);
    memcpy(&packet_buf[1], &mac[2], 4);
    return bswap32(calc_crc32((uint8_t *)packet_buf, 8, seed, 0));
}