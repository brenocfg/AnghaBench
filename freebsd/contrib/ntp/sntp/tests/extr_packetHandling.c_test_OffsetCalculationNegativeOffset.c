#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct pkt {int precision; int /*<<< orphan*/  xmt; int /*<<< orphan*/  rec; int /*<<< orphan*/  org; int /*<<< orphan*/  reftime; void* rootdisp; void* rootdelay; } ;
struct TYPE_5__ {unsigned long l_ui; unsigned long l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  DTOUFP (double) ; 
 int /*<<< orphan*/  HTONL_FP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* HTONS_FP (int /*<<< orphan*/ ) ; 
 scalar_t__ JAN_1970 ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_DOUBLE (double,double) ; 
 int /*<<< orphan*/  TSTOTV (TYPE_1__*,struct timeval*) ; 
 int ULOGTOD (int) ; 
 int /*<<< orphan*/  get_systime (TYPE_1__*) ; 
 int /*<<< orphan*/  offset_calculation (struct pkt*,int /*<<< orphan*/ ,struct timeval*,double*,double*,double*) ; 

void
test_OffsetCalculationNegativeOffset(void)
{
	struct pkt	rpkt;
	l_fp		reftime, tmp;
	struct timeval	dst;
	double		offset, precision, synch_distance;

	rpkt.precision = -1;
	rpkt.rootdelay = HTONS_FP(DTOUFP(0.5));
	rpkt.rootdisp = HTONS_FP(DTOUFP(0.5));
	
	/* Synch Distance is (0.5+0.5)/2.0, or 0.5 */
	get_systime(&reftime);
	HTONL_FP(&reftime, &rpkt.reftime);

	/* T1 - Originate timestamp */
	tmp.l_ui = 1000000001UL;
	tmp.l_uf = 0UL;
	HTONL_FP(&tmp, &rpkt.org);

	/* T2 - Receive timestamp */
	tmp.l_ui = 1000000000UL;
	tmp.l_uf = 2147483648UL;
	HTONL_FP(&tmp, &rpkt.rec);

	/*/ T3 - Transmit timestamp */
	tmp.l_ui = 1000000001UL;
	tmp.l_uf = 2147483648UL;
	HTONL_FP(&tmp, &rpkt.xmt);

	/* T4 - Destination timestamp as standard timeval */
	tmp.l_ui = 1000000003UL;
	tmp.l_uf = 0UL;

	TSTOTV(&tmp, &dst);
	dst.tv_sec -= JAN_1970;

	offset_calculation(&rpkt, LEN_PKT_NOMAC, &dst, &offset, &precision, &synch_distance);

	TEST_ASSERT_EQUAL_DOUBLE(-1, offset);
	TEST_ASSERT_EQUAL_DOUBLE(1. / ULOGTOD(1), precision);
	TEST_ASSERT_EQUAL_DOUBLE(1.3333483333333334, synch_distance);
}