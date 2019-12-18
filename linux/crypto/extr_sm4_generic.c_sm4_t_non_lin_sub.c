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
 size_t* sbox ; 

__attribute__((used)) static u32 sm4_t_non_lin_sub(u32 x)
{
	int i;
	u8 *b = (u8 *)&x;

	for (i = 0; i < 4; ++i)
		b[i] = sbox[b[i]];

	return x;
}