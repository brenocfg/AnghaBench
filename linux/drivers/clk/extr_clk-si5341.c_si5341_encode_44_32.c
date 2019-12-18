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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int*) ; 
 int regmap_bulk_write (struct regmap*,unsigned int,int*,int) ; 

__attribute__((used)) static int si5341_encode_44_32(struct regmap *regmap, unsigned int reg,
	u64 n_num, u32 n_den)
{
	u8 r[10];

	/* Shift left as far as possible without overflowing */
	while (!(n_num & BIT_ULL(43)) && !(n_den & BIT(31))) {
		n_num <<= 1;
		n_den <<= 1;
	}

	/* 44 bits (6 bytes) numerator */
	put_unaligned_le32(n_num, r);
	r[4] = (n_num >> 32) & 0xff;
	r[5] = (n_num >> 40) & 0x0f;
	/* 32 bits denominator */
	put_unaligned_le32(n_den, &r[6]);

	/* Program the fraction */
	return regmap_bulk_write(regmap, reg, r, sizeof(r));
}