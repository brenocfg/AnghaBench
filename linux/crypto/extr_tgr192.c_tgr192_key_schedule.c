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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static void tgr192_key_schedule(u64 * x)
{
	x[0] -= x[7] ^ 0xa5a5a5a5a5a5a5a5ULL;
	x[1] ^= x[0];
	x[2] += x[1];
	x[3] -= x[2] ^ ((~x[1]) << 19);
	x[4] ^= x[3];
	x[5] += x[4];
	x[6] -= x[5] ^ ((~x[4]) >> 23);
	x[7] ^= x[6];
	x[0] += x[7];
	x[1] -= x[0] ^ ((~x[7]) << 19);
	x[2] ^= x[1];
	x[3] += x[2];
	x[4] -= x[3] ^ ((~x[2]) >> 23);
	x[5] ^= x[4];
	x[6] += x[5];
	x[7] -= x[6] ^ 0x0123456789abcdefULL;
}