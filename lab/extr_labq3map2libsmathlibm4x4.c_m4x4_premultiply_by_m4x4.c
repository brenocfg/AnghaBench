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

void m4x4_premultiply_by_m4x4( m4x4_t dst, const m4x4_t src ){
	vec_t dst0, dst1, dst2, dst3;

#if 1

	dst0 = dst[0] * src[0] + dst[1] * src[4] + dst[2] * src[8] + dst[3] * src[12];
	dst1 = dst[0] * src[1] + dst[1] * src[5] + dst[2] * src[9] + dst[3] * src[13];
	dst2 = dst[0] * src[2] + dst[1] * src[6] + dst[2] * src[10] + dst[3] * src[14];
	dst3 = dst[0] * src[3] + dst[1] * src[7] + dst[2] * src[11] + dst[3] * src[15];
	dst[0] = dst0; dst[1] = dst1; dst[2] = dst2; dst[3] = dst3;

	dst0 = dst[4] * src[0] + dst[5] * src[4] + dst[6] * src[8] + dst[7] * src[12];
	dst1 = dst[4] * src[1] + dst[5] * src[5] + dst[6] * src[9] + dst[7] * src[13];
	dst2 = dst[4] * src[2] + dst[5] * src[6] + dst[6] * src[10] + dst[7] * src[14];
	dst3 = dst[4] * src[3] + dst[5] * src[7] + dst[6] * src[11] + dst[7] * src[15];
	dst[4] = dst0; dst[5] = dst1; dst[6] = dst2; dst[7] = dst3;

	dst0 = dst[8] * src[0] + dst[9] * src[4] + dst[10] * src[8] + dst[11] * src[12];
	dst1 = dst[8] * src[1] + dst[9] * src[5] + dst[10] * src[9] + dst[11] * src[13];
	dst2 = dst[8] * src[2] + dst[9] * src[6] + dst[10] * src[10] + dst[11] * src[14];
	dst3 = dst[8] * src[3] + dst[9] * src[7] + dst[10] * src[11] + dst[11] * src[15];
	dst[8] = dst0; dst[9] = dst1; dst[10] = dst2; dst[11] = dst3;

	dst0 = dst[12] * src[0] + dst[13] * src[4] + dst[14] * src[8] + dst[15] * src[12];
	dst1 = dst[12] * src[1] + dst[13] * src[5] + dst[14] * src[9] + dst[15] * src[13];
	dst2 = dst[12] * src[2] + dst[13] * src[6] + dst[14] * src[10] + dst[15] * src[14];
	dst3 = dst[12] * src[3] + dst[13] * src[7] + dst[14] * src[11] + dst[15] * src[15];
	dst[12] = dst0; dst[13] = dst1; dst[14] = dst2; dst[15] = dst3;

#else

	vec_t* p = dst;
	for ( int i = 0; i < 4; i++ )
	{
		dst1 =  src[0]  * p[0];
		dst2 =  src[1]  * p[0];
		dst3 =  src[2]  * p[0];
		dst4 =  src[3]  * p[0];
		dst1 += src[4]  * p[1];
		dst2 += src[5]  * p[1];
		dst3 += src[6]  * p[1];
		dst4 += src[7]  * p[1];
		dst1 += src[8]  * p[2];
		dst2 += src[9]  * p[2];
		dst4 += src[11] * p[2];
		dst3 += src[10] * p[2];
		dst1 += src[12] * p[3];
		dst2 += src[13] * p[3];
		dst3 += src[14] * p[3];
		dst4 += src[15] * p[3];

		*p++ = dst1;
		*p++ = dst2;
		*p++ = dst3;
		*p++ = dst4;
	}

#endif
}