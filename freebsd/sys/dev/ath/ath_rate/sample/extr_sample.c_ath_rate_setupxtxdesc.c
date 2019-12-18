#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t u_int8_t ;
struct txschedule {size_t r1; size_t r2; size_t r3; int /*<<< orphan*/  t3; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; } ;
struct sample_node {struct txschedule* sched; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; TYPE_2__* sc_currates; } ;
struct ath_node {int dummy; } ;
struct ath_desc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {size_t rateCode; size_t shortPreamble; } ;
typedef  TYPE_2__ HAL_RATE_TABLE ;

/* Variables and functions */
 struct sample_node* ATH_NODE_SAMPLE (struct ath_node*) ; 
 int /*<<< orphan*/  ath_hal_setupxtxdesc (int /*<<< orphan*/ ,struct ath_desc*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void
ath_rate_setupxtxdesc(struct ath_softc *sc, struct ath_node *an,
		      struct ath_desc *ds, int shortPreamble, u_int8_t rix)
{
	struct sample_node *sn = ATH_NODE_SAMPLE(an);
	const struct txschedule *sched = &sn->sched[rix];
	const HAL_RATE_TABLE *rt = sc->sc_currates;
	uint8_t rix1, s1code, rix2, s2code, rix3, s3code;

	/* XXX precalculate short preamble tables */
	rix1 = sched->r1;
	s1code = rt->info[rix1].rateCode
	       | (shortPreamble ? rt->info[rix1].shortPreamble : 0);
	rix2 = sched->r2;
	s2code = rt->info[rix2].rateCode
	       | (shortPreamble ? rt->info[rix2].shortPreamble : 0);
	rix3 = sched->r3;
	s3code = rt->info[rix3].rateCode
	       | (shortPreamble ? rt->info[rix3].shortPreamble : 0);
	ath_hal_setupxtxdesc(sc->sc_ah, ds,
	    s1code, sched->t1,		/* series 1 */
	    s2code, sched->t2,		/* series 2 */
	    s3code, sched->t3);		/* series 3 */
}