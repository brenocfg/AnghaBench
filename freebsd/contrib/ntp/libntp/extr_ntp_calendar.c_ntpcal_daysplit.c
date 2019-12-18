#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hi; int lo; } ;
struct TYPE_7__ {int /*<<< orphan*/  hi; } ;
struct TYPE_9__ {scalar_t__ q_s; int Q_s; TYPE_2__ D_s; TYPE_1__ d_s; } ;
typedef  TYPE_3__ vint64 ;
typedef  int uint32_t ;
struct TYPE_10__ {int lo; int /*<<< orphan*/  hi; } ;
typedef  TYPE_4__ ntpcal_split ;

/* Variables and functions */
 int SECSPERDAY ; 
 int int32_sflag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint32_2cpl_to_int32 (int) ; 

ntpcal_split
ntpcal_daysplit(
	const vint64 *ts
	)
{
	ntpcal_split res;
	uint32_t Q;

#   if defined(HAVE_INT64)
	
	/* Manual floor division by SECSPERDAY. This uses the one's
	 * complement trick, too, but without an extra flag value: The
	 * flag would be 64bit, and that's a bit of overkill on a 32bit
	 * target that has to use a register pair for a 64bit number.
	 */
	if (ts->q_s < 0)
		Q = ~(uint32_t)(~ts->Q_s / SECSPERDAY);
	else
		Q = (uint32_t)(ts->Q_s / SECSPERDAY);

#   else

	uint32_t ah, al, sflag, A;

	/* get operand into ah/al (either ts or ts' one's complement,
	 * for later floor division)
	 */
	sflag = int32_sflag(ts->d_s.hi);
	ah = sflag ^ ts->D_s.hi;
	al = sflag ^ ts->D_s.lo;

	/* Since 86400 == 128*675 we can drop the least 7 bits and
	 * divide by 675 instead of 86400. Then the maximum remainder
	 * after each devision step is 674, and we need 10 bits for
	 * that. So in the next step we can shift in 22 bits from the
	 * numerator.
	 *
	 * Therefore we load the accu with the top 13 bits (51..63) in
	 * the first shot. We don't have to remember the quotient -- it
	 * would be shifted out anyway.
	 */
	A = ah >> 19;
	if (A >= 675)
		A = (A % 675u);

	/* Now assemble the remainder with bits 29..50 from the
	 * numerator and divide. This creates the upper ten bits of the
	 * quotient. (Well, the top 22 bits of a 44bit result. But that
	 * will be truncated to 32 bits anyway.)
	 */
	A = (A << 19) | (ah & 0x0007FFFFu);
	A = (A <<  3) | (al >> 29);
	Q = A / 675u;
	A = A % 675u;

	/* Now assemble the remainder with bits 7..28 from the numerator
	 * and do a final division step.
	 */
	A = (A << 22) | ((al >> 7) & 0x003FFFFFu);
	Q = (Q << 22) | (A / 675u);

	/* The last 7 bits get simply dropped, as they have no affect on
	 * the quotient when dividing by 86400.
	 */

	/* apply sign correction and calculate the true floor
	 * remainder.
	 */
	Q ^= sflag;
	
#   endif
	
	res.hi = uint32_2cpl_to_int32(Q);
	res.lo = ts->D_s.lo - Q * SECSPERDAY;

	return res;
}