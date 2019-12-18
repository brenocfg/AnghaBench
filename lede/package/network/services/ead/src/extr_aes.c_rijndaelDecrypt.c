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
typedef  int u32 ;

/* Variables and functions */
 int const GETU32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PUTU32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ROUND (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const TD41 (int) ; 
 int const TD42 (int) ; 
 int const TD43 (int) ; 
 int const TD44 (int) ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  t ; 

__attribute__((used)) static void rijndaelDecrypt(const u32 rk[/*44*/], const u8 ct[16], u8 pt[16])
{
	u32 s0, s1, s2, s3, t0, t1, t2, t3;
	const int Nr = 10;
#ifndef FULL_UNROLL
	int r;
#endif /* ?FULL_UNROLL */

	/*
	 * map byte array block to cipher state
	 * and add initial round key:
	 */
	s0 = GETU32(ct     ) ^ rk[0];
	s1 = GETU32(ct +  4) ^ rk[1];
	s2 = GETU32(ct +  8) ^ rk[2];
	s3 = GETU32(ct + 12) ^ rk[3];

#define ROUND(i,d,s) \
d##0 = TD0(s##0) ^ TD1(s##3) ^ TD2(s##2) ^ TD3(s##1) ^ rk[4 * i]; \
d##1 = TD0(s##1) ^ TD1(s##0) ^ TD2(s##3) ^ TD3(s##2) ^ rk[4 * i + 1]; \
d##2 = TD0(s##2) ^ TD1(s##1) ^ TD2(s##0) ^ TD3(s##3) ^ rk[4 * i + 2]; \
d##3 = TD0(s##3) ^ TD1(s##2) ^ TD2(s##1) ^ TD3(s##0) ^ rk[4 * i + 3]

#ifdef FULL_UNROLL

	ROUND(1,t,s);
	ROUND(2,s,t);
	ROUND(3,t,s);
	ROUND(4,s,t);
	ROUND(5,t,s);
	ROUND(6,s,t);
	ROUND(7,t,s);
	ROUND(8,s,t);
	ROUND(9,t,s);

	rk += Nr << 2;

#else  /* !FULL_UNROLL */

	/* Nr - 1 full rounds: */
	r = Nr >> 1;
	for (;;) {
		ROUND(1,t,s);
		rk += 8;
		if (--r == 0)
			break;
		ROUND(0,s,t);
	}

#endif /* ?FULL_UNROLL */

#undef ROUND

	/*
	 * apply last round and
	 * map cipher state to byte array block:
	 */
	s0 = TD41(t0) ^ TD42(t3) ^ TD43(t2) ^ TD44(t1) ^ rk[0];
	PUTU32(pt     , s0);
	s1 = TD41(t1) ^ TD42(t0) ^ TD43(t3) ^ TD44(t2) ^ rk[1];
	PUTU32(pt +  4, s1);
	s2 = TD41(t2) ^ TD42(t1) ^ TD43(t0) ^ TD44(t3) ^ rk[2];
	PUTU32(pt +  8, s2);
	s3 = TD41(t3) ^ TD42(t2) ^ TD43(t1) ^ TD44(t0) ^ rk[3];
	PUTU32(pt + 12, s3);
}