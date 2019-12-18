#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct eventtimer {int dummy; } ;
struct decr_state {int mode; int div; } ;
typedef  int sbintime_t ;
struct TYPE_2__ {int et_frequency; } ;

/* Variables and functions */
 struct decr_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_DECAR ; 
 int /*<<< orphan*/  SPR_TCR ; 
 int TCR_ARE ; 
 int TCR_DIE ; 
 TYPE_1__ decr_et ; 
 int /*<<< orphan*/  decr_state ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdec (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
decr_et_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct decr_state *s = DPCPU_PTR(decr_state);
	uint32_t fdiv;
#ifdef BOOKE
	uint32_t tcr;
#endif

	if (period != 0) {
		s->mode = 1;
		s->div = (decr_et.et_frequency * period) >> 32;
	} else {
		s->mode = 2;
		s->div = 0;
	}
	if (first != 0)
		fdiv = (decr_et.et_frequency * first) >> 32;
	else
		fdiv = s->div;

#ifdef BOOKE
	tcr = mfspr(SPR_TCR);
	tcr |= TCR_DIE;
	if (s->mode == 1) {
		mtspr(SPR_DECAR, s->div);
		tcr |= TCR_ARE;
	} else
		tcr &= ~TCR_ARE;
	mtdec(fdiv);
	mtspr(SPR_TCR, tcr);
#else
	mtdec(fdiv);
#endif

	return (0);
}