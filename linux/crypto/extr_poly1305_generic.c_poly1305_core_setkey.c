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
struct poly1305_key {int* r; } ;

/* Variables and functions */
 int get_unaligned_le32 (int /*<<< orphan*/  const*) ; 

void poly1305_core_setkey(struct poly1305_key *key, const u8 *raw_key)
{
	/* r &= 0xffffffc0ffffffc0ffffffc0fffffff */
	key->r[0] = (get_unaligned_le32(raw_key +  0) >> 0) & 0x3ffffff;
	key->r[1] = (get_unaligned_le32(raw_key +  3) >> 2) & 0x3ffff03;
	key->r[2] = (get_unaligned_le32(raw_key +  6) >> 4) & 0x3ffc0ff;
	key->r[3] = (get_unaligned_le32(raw_key +  9) >> 6) & 0x3f03fff;
	key->r[4] = (get_unaligned_le32(raw_key + 12) >> 8) & 0x00fffff;
}