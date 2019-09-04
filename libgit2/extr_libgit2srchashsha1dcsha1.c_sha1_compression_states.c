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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1COMPRESS_FULL_ROUND1_STEP_EXPAND (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  SHA1COMPRESS_FULL_ROUND1_STEP_LOAD (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const*,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  SHA1COMPRESS_FULL_ROUND2_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  SHA1COMPRESS_FULL_ROUND3_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  SHA1COMPRESS_FULL_ROUND4_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int,scalar_t__) ; 

void sha1_compression_states(uint32_t ihv[5], const uint32_t m[16], uint32_t W[80], uint32_t states[80][5])
{
	uint32_t a = ihv[0], b = ihv[1], c = ihv[2], d = ihv[3], e = ihv[4];
	uint32_t temp;

#ifdef DOSTORESTATE00
	SHA1_STORE_STATE(0)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(a, b, c, d, e, m, W, 0, temp);

#ifdef DOSTORESTATE01
	SHA1_STORE_STATE(1)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(e, a, b, c, d, m, W, 1, temp);

#ifdef DOSTORESTATE02
	SHA1_STORE_STATE(2)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(d, e, a, b, c, m, W, 2, temp);

#ifdef DOSTORESTATE03
	SHA1_STORE_STATE(3)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(c, d, e, a, b, m, W, 3, temp);

#ifdef DOSTORESTATE04
	SHA1_STORE_STATE(4)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(b, c, d, e, a, m, W, 4, temp);

#ifdef DOSTORESTATE05
	SHA1_STORE_STATE(5)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(a, b, c, d, e, m, W, 5, temp);

#ifdef DOSTORESTATE06
	SHA1_STORE_STATE(6)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(e, a, b, c, d, m, W, 6, temp);

#ifdef DOSTORESTATE07
	SHA1_STORE_STATE(7)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(d, e, a, b, c, m, W, 7, temp);

#ifdef DOSTORESTATE08
	SHA1_STORE_STATE(8)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(c, d, e, a, b, m, W, 8, temp);

#ifdef DOSTORESTATE09
	SHA1_STORE_STATE(9)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(b, c, d, e, a, m, W, 9, temp);

#ifdef DOSTORESTATE10
	SHA1_STORE_STATE(10)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(a, b, c, d, e, m, W, 10, temp);

#ifdef DOSTORESTATE11
	SHA1_STORE_STATE(11)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(e, a, b, c, d, m, W, 11, temp);

#ifdef DOSTORESTATE12
	SHA1_STORE_STATE(12)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(d, e, a, b, c, m, W, 12, temp);

#ifdef DOSTORESTATE13
	SHA1_STORE_STATE(13)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(c, d, e, a, b, m, W, 13, temp);

#ifdef DOSTORESTATE14
	SHA1_STORE_STATE(14)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(b, c, d, e, a, m, W, 14, temp);

#ifdef DOSTORESTATE15
	SHA1_STORE_STATE(15)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_LOAD(a, b, c, d, e, m, W, 15, temp);

#ifdef DOSTORESTATE16
	SHA1_STORE_STATE(16)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_EXPAND(e, a, b, c, d, W, 16, temp);

#ifdef DOSTORESTATE17
	SHA1_STORE_STATE(17)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_EXPAND(d, e, a, b, c, W, 17, temp);

#ifdef DOSTORESTATE18
	SHA1_STORE_STATE(18)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_EXPAND(c, d, e, a, b, W, 18, temp);

#ifdef DOSTORESTATE19
	SHA1_STORE_STATE(19)
#endif
	SHA1COMPRESS_FULL_ROUND1_STEP_EXPAND(b, c, d, e, a, W, 19, temp);



#ifdef DOSTORESTATE20
	SHA1_STORE_STATE(20)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(a, b, c, d, e, W, 20, temp);

#ifdef DOSTORESTATE21
	SHA1_STORE_STATE(21)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(e, a, b, c, d, W, 21, temp);

#ifdef DOSTORESTATE22
	SHA1_STORE_STATE(22)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(d, e, a, b, c, W, 22, temp);

#ifdef DOSTORESTATE23
	SHA1_STORE_STATE(23)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(c, d, e, a, b, W, 23, temp);

#ifdef DOSTORESTATE24
	SHA1_STORE_STATE(24)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(b, c, d, e, a, W, 24, temp);

#ifdef DOSTORESTATE25
	SHA1_STORE_STATE(25)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(a, b, c, d, e, W, 25, temp);

#ifdef DOSTORESTATE26
	SHA1_STORE_STATE(26)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(e, a, b, c, d, W, 26, temp);

#ifdef DOSTORESTATE27
	SHA1_STORE_STATE(27)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(d, e, a, b, c, W, 27, temp);

#ifdef DOSTORESTATE28
	SHA1_STORE_STATE(28)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(c, d, e, a, b, W, 28, temp);

#ifdef DOSTORESTATE29
	SHA1_STORE_STATE(29)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(b, c, d, e, a, W, 29, temp);

#ifdef DOSTORESTATE30
	SHA1_STORE_STATE(30)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(a, b, c, d, e, W, 30, temp);

#ifdef DOSTORESTATE31
	SHA1_STORE_STATE(31)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(e, a, b, c, d, W, 31, temp);

#ifdef DOSTORESTATE32
	SHA1_STORE_STATE(32)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(d, e, a, b, c, W, 32, temp);

#ifdef DOSTORESTATE33
	SHA1_STORE_STATE(33)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(c, d, e, a, b, W, 33, temp);

#ifdef DOSTORESTATE34
	SHA1_STORE_STATE(34)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(b, c, d, e, a, W, 34, temp);

#ifdef DOSTORESTATE35
	SHA1_STORE_STATE(35)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(a, b, c, d, e, W, 35, temp);

#ifdef DOSTORESTATE36
	SHA1_STORE_STATE(36)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(e, a, b, c, d, W, 36, temp);

#ifdef DOSTORESTATE37
	SHA1_STORE_STATE(37)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(d, e, a, b, c, W, 37, temp);

#ifdef DOSTORESTATE38
	SHA1_STORE_STATE(38)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(c, d, e, a, b, W, 38, temp);

#ifdef DOSTORESTATE39
	SHA1_STORE_STATE(39)
#endif
	SHA1COMPRESS_FULL_ROUND2_STEP(b, c, d, e, a, W, 39, temp);



#ifdef DOSTORESTATE40
	SHA1_STORE_STATE(40)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(a, b, c, d, e, W, 40, temp);

#ifdef DOSTORESTATE41
	SHA1_STORE_STATE(41)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(e, a, b, c, d, W, 41, temp);

#ifdef DOSTORESTATE42
	SHA1_STORE_STATE(42)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(d, e, a, b, c, W, 42, temp);

#ifdef DOSTORESTATE43
	SHA1_STORE_STATE(43)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(c, d, e, a, b, W, 43, temp);

#ifdef DOSTORESTATE44
	SHA1_STORE_STATE(44)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(b, c, d, e, a, W, 44, temp);

#ifdef DOSTORESTATE45
	SHA1_STORE_STATE(45)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(a, b, c, d, e, W, 45, temp);

#ifdef DOSTORESTATE46
	SHA1_STORE_STATE(46)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(e, a, b, c, d, W, 46, temp);

#ifdef DOSTORESTATE47
	SHA1_STORE_STATE(47)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(d, e, a, b, c, W, 47, temp);

#ifdef DOSTORESTATE48
	SHA1_STORE_STATE(48)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(c, d, e, a, b, W, 48, temp);

#ifdef DOSTORESTATE49
	SHA1_STORE_STATE(49)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(b, c, d, e, a, W, 49, temp);

#ifdef DOSTORESTATE50
	SHA1_STORE_STATE(50)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(a, b, c, d, e, W, 50, temp);

#ifdef DOSTORESTATE51
	SHA1_STORE_STATE(51)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(e, a, b, c, d, W, 51, temp);

#ifdef DOSTORESTATE52
	SHA1_STORE_STATE(52)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(d, e, a, b, c, W, 52, temp);

#ifdef DOSTORESTATE53
	SHA1_STORE_STATE(53)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(c, d, e, a, b, W, 53, temp);

#ifdef DOSTORESTATE54
	SHA1_STORE_STATE(54)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(b, c, d, e, a, W, 54, temp);

#ifdef DOSTORESTATE55
	SHA1_STORE_STATE(55)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(a, b, c, d, e, W, 55, temp);

#ifdef DOSTORESTATE56
	SHA1_STORE_STATE(56)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(e, a, b, c, d, W, 56, temp);

#ifdef DOSTORESTATE57
	SHA1_STORE_STATE(57)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(d, e, a, b, c, W, 57, temp);

#ifdef DOSTORESTATE58
	SHA1_STORE_STATE(58)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(c, d, e, a, b, W, 58, temp);

#ifdef DOSTORESTATE59
	SHA1_STORE_STATE(59)
#endif
	SHA1COMPRESS_FULL_ROUND3_STEP(b, c, d, e, a, W, 59, temp);




#ifdef DOSTORESTATE60
	SHA1_STORE_STATE(60)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(a, b, c, d, e, W, 60, temp);

#ifdef DOSTORESTATE61
	SHA1_STORE_STATE(61)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(e, a, b, c, d, W, 61, temp);

#ifdef DOSTORESTATE62
	SHA1_STORE_STATE(62)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(d, e, a, b, c, W, 62, temp);

#ifdef DOSTORESTATE63
	SHA1_STORE_STATE(63)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(c, d, e, a, b, W, 63, temp);

#ifdef DOSTORESTATE64
	SHA1_STORE_STATE(64)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(b, c, d, e, a, W, 64, temp);

#ifdef DOSTORESTATE65
	SHA1_STORE_STATE(65)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(a, b, c, d, e, W, 65, temp);

#ifdef DOSTORESTATE66
	SHA1_STORE_STATE(66)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(e, a, b, c, d, W, 66, temp);

#ifdef DOSTORESTATE67
	SHA1_STORE_STATE(67)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(d, e, a, b, c, W, 67, temp);

#ifdef DOSTORESTATE68
	SHA1_STORE_STATE(68)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(c, d, e, a, b, W, 68, temp);

#ifdef DOSTORESTATE69
	SHA1_STORE_STATE(69)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(b, c, d, e, a, W, 69, temp);

#ifdef DOSTORESTATE70
	SHA1_STORE_STATE(70)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(a, b, c, d, e, W, 70, temp);

#ifdef DOSTORESTATE71
	SHA1_STORE_STATE(71)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(e, a, b, c, d, W, 71, temp);

#ifdef DOSTORESTATE72
	SHA1_STORE_STATE(72)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(d, e, a, b, c, W, 72, temp);

#ifdef DOSTORESTATE73
	SHA1_STORE_STATE(73)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(c, d, e, a, b, W, 73, temp);

#ifdef DOSTORESTATE74
	SHA1_STORE_STATE(74)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(b, c, d, e, a, W, 74, temp);

#ifdef DOSTORESTATE75
	SHA1_STORE_STATE(75)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(a, b, c, d, e, W, 75, temp);

#ifdef DOSTORESTATE76
	SHA1_STORE_STATE(76)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(e, a, b, c, d, W, 76, temp);

#ifdef DOSTORESTATE77
	SHA1_STORE_STATE(77)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(d, e, a, b, c, W, 77, temp);

#ifdef DOSTORESTATE78
	SHA1_STORE_STATE(78)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(c, d, e, a, b, W, 78, temp);

#ifdef DOSTORESTATE79
	SHA1_STORE_STATE(79)
#endif
	SHA1COMPRESS_FULL_ROUND4_STEP(b, c, d, e, a, W, 79, temp);



	ihv[0] += a; ihv[1] += b; ihv[2] += c; ihv[3] += d; ihv[4] += e;
}