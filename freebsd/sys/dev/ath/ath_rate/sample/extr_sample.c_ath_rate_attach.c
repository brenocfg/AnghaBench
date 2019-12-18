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
struct ath_ratectrl {int arc_space; } ;
struct sample_softc {int smoothing_rate; int smoothing_minpackets; int sample_rate; int max_successive_failures; int stale_failure_timeout; int min_switch; struct ath_ratectrl arc; } ;
struct sample_node {int dummy; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ath_rate_sysctlattach (struct ath_softc*,struct sample_softc*) ; 
 int hz ; 
 struct sample_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

struct ath_ratectrl *
ath_rate_attach(struct ath_softc *sc)
{
	struct sample_softc *ssc;
	
	ssc = malloc(sizeof(struct sample_softc), M_DEVBUF, M_NOWAIT|M_ZERO);
	if (ssc == NULL)
		return NULL;
	ssc->arc.arc_space = sizeof(struct sample_node);
	ssc->smoothing_rate = 75;		/* ewma percentage ([0..99]) */
	ssc->smoothing_minpackets = 100 / (100 - ssc->smoothing_rate);
	ssc->sample_rate = 10;			/* %time to try diff tx rates */
	ssc->max_successive_failures = 3;	/* threshold for rate sampling*/
	ssc->stale_failure_timeout = 10 * hz;	/* 10 seconds */
	ssc->min_switch = hz;			/* 1 second */
	ath_rate_sysctlattach(sc, ssc);
	return &ssc->arc;
}