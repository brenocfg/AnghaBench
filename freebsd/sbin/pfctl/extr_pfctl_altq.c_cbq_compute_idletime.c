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
typedef  int u_int ;
struct pfctl {int opts; } ;
struct cbq_opts {int minburst; int maxburst; int maxpktsize; int ns_per_byte; int maxidle; int minidle; int offtime; scalar_t__ pktsize; } ;
struct TYPE_2__ {struct cbq_opts cbq_opts; } ;
struct pf_altq {scalar_t__ bandwidth; char* qname; scalar_t__ ifbandwidth; TYPE_1__ pq_u; } ;

/* Variables and functions */
 int INT_MAX ; 
 int PF_OPT_QUIET ; 
 int RM_FILTER_GAIN ; 
 double RM_NS_PER_SEC ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 double pow (double,double) ; 
 int /*<<< orphan*/  rate2str (double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbq_compute_idletime(struct pfctl *pf, struct pf_altq *pa)
{
	struct cbq_opts	*opts;
	double		 maxidle_s, maxidle, minidle;
	double		 offtime, nsPerByte, ifnsPerByte, ptime, cptime;
	double		 z, g, f, gton, gtom;
	u_int		 minburst, maxburst;

	opts = &pa->pq_u.cbq_opts;
	ifnsPerByte = (1.0 / (double)pa->ifbandwidth) * RM_NS_PER_SEC * 8;
	minburst = opts->minburst;
	maxburst = opts->maxburst;

	if (pa->bandwidth == 0)
		f = 0.0001;	/* small enough? */
	else
		f = ((double) pa->bandwidth / (double) pa->ifbandwidth);

	nsPerByte = ifnsPerByte / f;
	ptime = (double)opts->pktsize * ifnsPerByte;
	cptime = ptime * (1.0 - f) / f;

	if (nsPerByte * (double)opts->maxpktsize > (double)INT_MAX) {
		/*
		 * this causes integer overflow in kernel!
		 * (bandwidth < 6Kbps when max_pkt_size=1500)
		 */
		if (pa->bandwidth != 0 && (pf->opts & PF_OPT_QUIET) == 0) {
			warnx("queue bandwidth must be larger than %s",
			    rate2str(ifnsPerByte * (double)opts->maxpktsize /
			    (double)INT_MAX * (double)pa->ifbandwidth));
			fprintf(stderr, "cbq: queue %s is too slow!\n",
			    pa->qname);
		}
		nsPerByte = (double)(INT_MAX / opts->maxpktsize);
	}

	if (maxburst == 0) {  /* use default */
		if (cptime > 10.0 * 1000000)
			maxburst = 4;
		else
			maxburst = 16;
	}
	if (minburst == 0)  /* use default */
		minburst = 2;
	if (minburst > maxburst)
		minburst = maxburst;

	z = (double)(1 << RM_FILTER_GAIN);
	g = (1.0 - 1.0 / z);
	gton = pow(g, (double)maxburst);
	gtom = pow(g, (double)(minburst-1));
	maxidle = ((1.0 / f - 1.0) * ((1.0 - gton) / gton));
	maxidle_s = (1.0 - g);
	if (maxidle > maxidle_s)
		maxidle = ptime * maxidle;
	else
		maxidle = ptime * maxidle_s;
	offtime = cptime * (1.0 + 1.0/(1.0 - g) * (1.0 - gtom) / gtom);
	minidle = -((double)opts->maxpktsize * (double)nsPerByte);

	/* scale parameters */
	maxidle = ((maxidle * 8.0) / nsPerByte) *
	    pow(2.0, (double)RM_FILTER_GAIN);
	offtime = (offtime * 8.0) / nsPerByte *
	    pow(2.0, (double)RM_FILTER_GAIN);
	minidle = ((minidle * 8.0) / nsPerByte) *
	    pow(2.0, (double)RM_FILTER_GAIN);

	maxidle = maxidle / 1000.0;
	offtime = offtime / 1000.0;
	minidle = minidle / 1000.0;

	opts->minburst = minburst;
	opts->maxburst = maxburst;
	opts->ns_per_byte = (u_int)nsPerByte;
	opts->maxidle = (u_int)fabs(maxidle);
	opts->minidle = (int)minidle;
	opts->offtime = (u_int)fabs(offtime);

	return (0);
}