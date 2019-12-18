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
typedef  int /*<<< orphan*/  op_t ;

/* Variables and functions */
 int OPSIZ ; 

__attribute__((used)) static void _wordcopy_fwd_aligned(long int dstp, long int srcp, size_t len)
{
	while (len > 7) {
		register op_t a0, a1, a2, a3, a4, a5, a6, a7;

		a0 = ((op_t *) srcp)[0];
		a1 = ((op_t *) srcp)[1];
		a2 = ((op_t *) srcp)[2];
		a3 = ((op_t *) srcp)[3];
		a4 = ((op_t *) srcp)[4];
		a5 = ((op_t *) srcp)[5];
		a6 = ((op_t *) srcp)[6];
		a7 = ((op_t *) srcp)[7];
		((op_t *) dstp)[0] = a0;
		((op_t *) dstp)[1] = a1;
		((op_t *) dstp)[2] = a2;
		((op_t *) dstp)[3] = a3;
		((op_t *) dstp)[4] = a4;
		((op_t *) dstp)[5] = a5;
		((op_t *) dstp)[6] = a6;
		((op_t *) dstp)[7] = a7;

		srcp += 8 * OPSIZ;
		dstp += 8 * OPSIZ;
		len -= 8;
	}
	while (len > 0) {
		*(op_t *)dstp = *(op_t *)srcp;

		srcp += OPSIZ;
		dstp += OPSIZ;
		len -= 1;
	}
}