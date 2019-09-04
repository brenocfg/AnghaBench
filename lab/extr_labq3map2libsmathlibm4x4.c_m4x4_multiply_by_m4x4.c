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
typedef  int vec_t ;
typedef  int* m4x4_t ;

/* Variables and functions */

void m4x4_multiply_by_m4x4( m4x4_t dst, const m4x4_t src ){
	vec_t dst0, dst1, dst2, dst3;

#if 1

	dst0 = src[0] * dst[0] + src[1] * dst[4] + src[2] * dst[8] + src[3] * dst[12];
	dst1 = src[4] * dst[0] + src[5] * dst[4] + src[6] * dst[8] + src[7] * dst[12];
	dst2 = src[8] * dst[0] + src[9] * dst[4] + src[10] * dst[8] + src[11] * dst[12];
	dst3 = src[12] * dst[0] + src[13] * dst[4] + src[14] * dst[8] + src[15] * dst[12];
	dst[0] = dst0; dst[4] = dst1; dst[8] = dst2; dst[12] = dst3;

	dst0 = src[0] * dst[1] + src[1] * dst[5] + src[2] * dst[9] + src[3] * dst[13];
	dst1 = src[4] * dst[1] + src[5] * dst[5] + src[6] * dst[9] + src[7] * dst[13];
	dst2 = src[8] * dst[1] + src[9] * dst[5] + src[10] * dst[9] + src[11] * dst[13];
	dst3 = src[12] * dst[1] + src[13] * dst[5] + src[14] * dst[9] + src[15] * dst[13];
	dst[1] = dst0; dst[5] = dst1; dst[9] = dst2; dst[13] = dst3;

	dst0 = src[0] * dst[2] + src[1] * dst[6] + src[2] * dst[10] + src[3] * dst[14];
	dst1 = src[4] * dst[2] + src[5] * dst[6] + src[6] * dst[10] + src[7] * dst[14];
	dst2 = src[8] * dst[2] + src[9] * dst[6] + src[10] * dst[10] + src[11] * dst[14];
	dst3 = src[12] * dst[2] + src[13] * dst[6] + src[14] * dst[10] + src[15] * dst[14];
	dst[2] = dst0; dst[6] = dst1; dst[10] = dst2; dst[14] = dst3;

	dst0 = src[0] * dst[3] + src[1] * dst[7] + src[2] * dst[11] + src[3] * dst[15];
	dst1 = src[4] * dst[3] + src[5] * dst[7] + src[6] * dst[11] + src[7] * dst[15];
	dst2 = src[8] * dst[3] + src[9] * dst[7] + src[10] * dst[11] + src[11] * dst[15];
	dst3 = src[12] * dst[3] + src[13] * dst[7] + src[14] * dst[11] + src[15] * dst[15];
	dst[3] = dst0; dst[7] = dst1; dst[11] = dst2; dst[15] = dst3;

#else

	vec_t * p = dst;
	for ( int i = 0; i < 4; i++ )
	{
		dst1 =  src[0]  * p[0];
		dst1 += src[1]  * p[4];
		dst1 += src[2]  * p[8];
		dst1 += src[3]  * p[12];
		dst2 =  src[4]  * p[0];
		dst2 += src[5]  * p[4];
		dst2 += src[6]  * p[8];
		dst2 += src[7]  * p[12];
		dst3 =  src[8]  * p[0];
		dst3 += src[9]  * p[4];
		dst3 += src[10] * p[8];
		dst3 += src[11] * p[12];
		dst4 =  src[12] * p[0];
		dst4 += src[13] * p[4];
		dst4 += src[14] * p[8];
		dst4 += src[15] * p[12];

		p[0] = dst1;
		p[4] = dst2;
		p[8] = dst3;
		p[12] = dst4;
		p++;
	}

#endif
}