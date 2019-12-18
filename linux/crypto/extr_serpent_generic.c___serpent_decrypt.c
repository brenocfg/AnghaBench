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
typedef  int /*<<< orphan*/  u32 ;
struct serpent_ctx {int /*<<< orphan*/ * expkey; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  K (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SI0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/  const) ; 

void __serpent_decrypt(struct serpent_ctx *ctx, u8 *dst, const u8 *src)
{
	const u32 *k = ctx->expkey;
	const __le32 *s = (const __le32 *)src;
	__le32	*d = (__le32 *)dst;
	u32	r0, r1, r2, r3, r4;

	r0 = le32_to_cpu(s[0]);
	r1 = le32_to_cpu(s[1]);
	r2 = le32_to_cpu(s[2]);
	r3 = le32_to_cpu(s[3]);

					K(r0, r1, r2, r3, 32);
	SI7(r0, r1, r2, r3, r4);	KL(r1, r3, r0, r4, r2, 31);
	SI6(r1, r3, r0, r4, r2);	KL(r0, r2, r4, r1, r3, 30);
	SI5(r0, r2, r4, r1, r3);	KL(r2, r3, r0, r4, r1, 29);
	SI4(r2, r3, r0, r4, r1);	KL(r2, r0, r1, r4, r3, 28);
	SI3(r2, r0, r1, r4, r3);	KL(r1, r2, r3, r4, r0, 27);
	SI2(r1, r2, r3, r4, r0);	KL(r2, r0, r4, r3, r1, 26);
	SI1(r2, r0, r4, r3, r1);	KL(r1, r0, r4, r3, r2, 25);
	SI0(r1, r0, r4, r3, r2);	KL(r4, r2, r0, r1, r3, 24);
	SI7(r4, r2, r0, r1, r3);	KL(r2, r1, r4, r3, r0, 23);
	SI6(r2, r1, r4, r3, r0);	KL(r4, r0, r3, r2, r1, 22);
	SI5(r4, r0, r3, r2, r1);	KL(r0, r1, r4, r3, r2, 21);
	SI4(r0, r1, r4, r3, r2);	KL(r0, r4, r2, r3, r1, 20);
	SI3(r0, r4, r2, r3, r1);	KL(r2, r0, r1, r3, r4, 19);
	SI2(r2, r0, r1, r3, r4);	KL(r0, r4, r3, r1, r2, 18);
	SI1(r0, r4, r3, r1, r2);	KL(r2, r4, r3, r1, r0, 17);
	SI0(r2, r4, r3, r1, r0);	KL(r3, r0, r4, r2, r1, 16);
	SI7(r3, r0, r4, r2, r1);	KL(r0, r2, r3, r1, r4, 15);
	SI6(r0, r2, r3, r1, r4);	KL(r3, r4, r1, r0, r2, 14);
	SI5(r3, r4, r1, r0, r2);	KL(r4, r2, r3, r1, r0, 13);
	SI4(r4, r2, r3, r1, r0);	KL(r4, r3, r0, r1, r2, 12);
	SI3(r4, r3, r0, r1, r2);	KL(r0, r4, r2, r1, r3, 11);
	SI2(r0, r4, r2, r1, r3);	KL(r4, r3, r1, r2, r0, 10);
	SI1(r4, r3, r1, r2, r0);	KL(r0, r3, r1, r2, r4, 9);
	SI0(r0, r3, r1, r2, r4);	KL(r1, r4, r3, r0, r2, 8);
	SI7(r1, r4, r3, r0, r2);	KL(r4, r0, r1, r2, r3, 7);
	SI6(r4, r0, r1, r2, r3);	KL(r1, r3, r2, r4, r0, 6);
	SI5(r1, r3, r2, r4, r0);	KL(r3, r0, r1, r2, r4, 5);
	SI4(r3, r0, r1, r2, r4);	KL(r3, r1, r4, r2, r0, 4);
	SI3(r3, r1, r4, r2, r0);	KL(r4, r3, r0, r2, r1, 3);
	SI2(r4, r3, r0, r2, r1);	KL(r3, r1, r2, r0, r4, 2);
	SI1(r3, r1, r2, r0, r4);	KL(r4, r1, r2, r0, r3, 1);
	SI0(r4, r1, r2, r0, r3);	K(r2, r3, r1, r4, 0);

	d[0] = cpu_to_le32(r2);
	d[1] = cpu_to_le32(r3);
	d[2] = cpu_to_le32(r1);
	d[3] = cpu_to_le32(r4);
}