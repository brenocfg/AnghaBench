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
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */

__wsum csum_partial(const void *buff, int len, __wsum sum)
{
	unsigned long tmp1, tmp2;
	  /*
	   * Experiments with ethernet and slip connections show that buff
	   * is aligned on either a 2-byte or 4-byte boundary.
	   */
	__asm__("movel %2,%3\n\t"
		"btst #1,%3\n\t"	/* Check alignment */
		"jeq 2f\n\t"
		"subql #2,%1\n\t"	/* buff%4==2: treat first word */
		"jgt 1f\n\t"
		"addql #2,%1\n\t"	/* len was == 2, treat only rest */
		"jra 4f\n"
	     "1:\t"
		"addw %2@+,%0\n\t"	/* add first word to sum */
		"clrl %3\n\t"
		"addxl %3,%0\n"		/* add X bit */
	     "2:\t"
		/* unrolled loop for the main part: do 8 longs at once */
		"movel %1,%3\n\t"	/* save len in tmp1 */
		"lsrl #5,%1\n\t"	/* len/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subql #1,%1\n"
	     "1:\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"dbra %1,1b\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n\t"	/* add X bit */
		"clrw %1\n\t"
		"subql #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movel %3,%1\n\t"	/* restore len from tmp1 */
		"andw #0x1c,%3\n\t"	/* number of rest longs */
		"jeq 4f\n\t"
		"lsrw #2,%3\n\t"
		"subqw #1,%3\n"
	     "3:\t"
		/* loop for rest longs */
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"dbra %3,3b\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "4:\t"
		/* now check for rest bytes that do not fit into longs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"clrl %4\n\t"		/* clear tmp2 for rest bytes */
		"subqw #2,%1\n\t"
		"jlt 5f\n\t"
		"movew %2@+,%4\n\t"	/* have rest >= 2: get word */
		"swap %4\n\t"		/* into bits 16..31 */
		"tstw %1\n\t"		/* another byte? */
		"jeq 6f\n"
	     "5:\t"
		"moveb %2@,%4\n\t"	/* have odd rest: get byte */
		"lslw #8,%4\n\t"	/* into bits 8..15; 16..31 untouched */
	     "6:\t"
		"addl %4,%0\n\t"	/* now add rest long to sum */
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "7:\t"
		: "=d" (sum), "=d" (len), "=a" (buff),
		  "=&d" (tmp1), "=&d" (tmp2)
		: "0" (sum), "1" (len), "2" (buff)
	    );
	return(sum);
}