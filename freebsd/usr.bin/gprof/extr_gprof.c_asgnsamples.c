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
struct TYPE_2__ {unsigned long svalue; int value; unsigned long time; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HISTORICAL_SCALE_2 ; 
 int SAMPLEDEBUG ; 
 int /*<<< orphan*/  alignentries () ; 
 int debug ; 
 int highpc ; 
 unsigned long lowpc ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 TYPE_1__* nl ; 
 int nname ; 
 int nsamples ; 
 int /*<<< orphan*/  printf (char*,double,...) ; 
 double* samples ; 
 int scale ; 
 double totime ; 

void
asgnsamples(void)
{
    register int	j;
    double		ccnt;
    double		thetime;
    unsigned long	pcl, pch;
    register int	i;
    unsigned long	overlap;
    unsigned long	svalue0, svalue1;

    /* read samples and assign to namelist symbols */
    scale = highpc - lowpc;
    scale /= nsamples;
    alignentries();
    for (i = 0, j = 1; i < nsamples; i++) {
	ccnt = samples[i];
	if (ccnt == 0)
		continue;
	pcl = lowpc + (unsigned long)(scale * i);
	pch = lowpc + (unsigned long)(scale * (i + 1));
	thetime = ccnt;
#	ifdef DEBUG
	    if ( debug & SAMPLEDEBUG ) {
		printf( "[asgnsamples] pcl 0x%lx pch 0x%lx ccnt %.0f\n" ,
			pcl , pch , ccnt );
	    }
#	endif /* DEBUG */
	totime += thetime;
	for (j = j - 1; j < nname; j++) {
	    svalue0 = nl[j].svalue;
	    svalue1 = nl[j+1].svalue;
		/*
		 *	if high end of tick is below entry address,
		 *	go for next tick.
		 */
	    if (pch < svalue0)
		    break;
		/*
		 *	if low end of tick into next routine,
		 *	go for next routine.
		 */
	    if (pcl >= svalue1)
		    continue;
	    overlap = min(pch, svalue1) - max(pcl, svalue0);
	    if (overlap > 0) {
#		ifdef DEBUG
		    if (debug & SAMPLEDEBUG) {
			printf("[asgnsamples] (0x%lx->0x%lx-0x%lx) %s gets %f ticks %lu overlap\n",
				nl[j].value / HISTORICAL_SCALE_2,
				svalue0, svalue1, nl[j].name,
				overlap * thetime / scale, overlap);
		    }
#		endif /* DEBUG */
		nl[j].time += overlap * thetime / scale;
	    }
	}
    }
#   ifdef DEBUG
	if (debug & SAMPLEDEBUG) {
	    printf("[asgnsamples] totime %f\n", totime);
	}
#   endif /* DEBUG */
}