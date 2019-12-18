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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t* aes_sbox ; 

__attribute__((used)) static inline u32 aes_ks_subword(const u32 w)
{
	u8 bytes[4];

	*(u32 *)(&bytes[0]) = w;
	bytes[0] = aes_sbox[bytes[0]];
	bytes[1] = aes_sbox[bytes[1]];
	bytes[2] = aes_sbox[bytes[2]];
	bytes[3] = aes_sbox[bytes[3]];
	return *(u32 *)(&bytes[0]);
}