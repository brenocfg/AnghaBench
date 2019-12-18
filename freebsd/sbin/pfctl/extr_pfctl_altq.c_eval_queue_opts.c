#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_24__ {int /*<<< orphan*/  ecn; int /*<<< orphan*/  interval; int /*<<< orphan*/  target; } ;
struct TYPE_21__ {int /*<<< orphan*/  lssc_d; void* lssc_m2; void* lssc_m1; void* hogs_m1; int /*<<< orphan*/  nbuckets; int /*<<< orphan*/  flags; } ;
struct TYPE_18__ {int /*<<< orphan*/  ulsc_d; void* ulsc_m2; void* ulsc_m1; int /*<<< orphan*/  rtsc_d; void* rtsc_m2; void* rtsc_m1; int /*<<< orphan*/  lssc_d; void* lssc_m2; void* lssc_m1; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {TYPE_9__ codel_opts; TYPE_6__ fairq_opts; TYPE_3__ hfsc_opts; int /*<<< orphan*/  priq_opts; int /*<<< orphan*/  cbq_opts; } ;
struct pf_altq {int scheduler; TYPE_10__ pq_u; } ;
struct TYPE_14__ {int /*<<< orphan*/  ecn; int /*<<< orphan*/  interval; int /*<<< orphan*/  target; } ;
struct TYPE_22__ {int /*<<< orphan*/  d; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; int /*<<< orphan*/  used; } ;
struct TYPE_23__ {TYPE_7__ linkshare; int /*<<< orphan*/  hogs_bw; int /*<<< orphan*/  nbuckets; int /*<<< orphan*/  flags; } ;
struct TYPE_19__ {int /*<<< orphan*/  d; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; int /*<<< orphan*/  used; } ;
struct TYPE_17__ {int /*<<< orphan*/  d; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; int /*<<< orphan*/  used; } ;
struct TYPE_16__ {int /*<<< orphan*/  d; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; int /*<<< orphan*/  used; } ;
struct TYPE_20__ {TYPE_4__ upperlimit; TYPE_2__ realtime; TYPE_1__ linkshare; int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {TYPE_11__ codel_opts; TYPE_8__ fairq_opts; TYPE_5__ hfsc_opts; int /*<<< orphan*/  priq_opts; int /*<<< orphan*/  cbq_opts; } ;
struct node_queue_opt {int /*<<< orphan*/  qtype; TYPE_12__ data; } ;

/* Variables and functions */
#define  ALTQT_CBQ 132 
#define  ALTQT_CODEL 131 
#define  ALTQT_FAIRQ 130 
#define  ALTQT_HFSC 129 
#define  ALTQT_PRIQ 128 
 void* eval_bwspec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
eval_queue_opts(struct pf_altq *pa, struct node_queue_opt *opts,
    u_int64_t ref_bw)
{
	int	errors = 0;

	switch (pa->scheduler) {
	case ALTQT_CBQ:
		pa->pq_u.cbq_opts = opts->data.cbq_opts;
		break;
	case ALTQT_PRIQ:
		pa->pq_u.priq_opts = opts->data.priq_opts;
		break;
	case ALTQT_HFSC:
		pa->pq_u.hfsc_opts.flags = opts->data.hfsc_opts.flags;
		if (opts->data.hfsc_opts.linkshare.used) {
			pa->pq_u.hfsc_opts.lssc_m1 =
			    eval_bwspec(&opts->data.hfsc_opts.linkshare.m1,
			    ref_bw);
			pa->pq_u.hfsc_opts.lssc_m2 =
			    eval_bwspec(&opts->data.hfsc_opts.linkshare.m2,
			    ref_bw);
			pa->pq_u.hfsc_opts.lssc_d =
			    opts->data.hfsc_opts.linkshare.d;
		}
		if (opts->data.hfsc_opts.realtime.used) {
			pa->pq_u.hfsc_opts.rtsc_m1 =
			    eval_bwspec(&opts->data.hfsc_opts.realtime.m1,
			    ref_bw);
			pa->pq_u.hfsc_opts.rtsc_m2 =
			    eval_bwspec(&opts->data.hfsc_opts.realtime.m2,
			    ref_bw);
			pa->pq_u.hfsc_opts.rtsc_d =
			    opts->data.hfsc_opts.realtime.d;
		}
		if (opts->data.hfsc_opts.upperlimit.used) {
			pa->pq_u.hfsc_opts.ulsc_m1 =
			    eval_bwspec(&opts->data.hfsc_opts.upperlimit.m1,
			    ref_bw);
			pa->pq_u.hfsc_opts.ulsc_m2 =
			    eval_bwspec(&opts->data.hfsc_opts.upperlimit.m2,
			    ref_bw);
			pa->pq_u.hfsc_opts.ulsc_d =
			    opts->data.hfsc_opts.upperlimit.d;
		}
		break;
	case ALTQT_FAIRQ:
		pa->pq_u.fairq_opts.flags = opts->data.fairq_opts.flags;
		pa->pq_u.fairq_opts.nbuckets = opts->data.fairq_opts.nbuckets;
		pa->pq_u.fairq_opts.hogs_m1 =
			eval_bwspec(&opts->data.fairq_opts.hogs_bw, ref_bw);

		if (opts->data.fairq_opts.linkshare.used) {
			pa->pq_u.fairq_opts.lssc_m1 =
			    eval_bwspec(&opts->data.fairq_opts.linkshare.m1,
			    ref_bw);
			pa->pq_u.fairq_opts.lssc_m2 =
			    eval_bwspec(&opts->data.fairq_opts.linkshare.m2,
			    ref_bw);
			pa->pq_u.fairq_opts.lssc_d =
			    opts->data.fairq_opts.linkshare.d;
		}
		break;
	case ALTQT_CODEL:
		pa->pq_u.codel_opts.target = opts->data.codel_opts.target;
		pa->pq_u.codel_opts.interval = opts->data.codel_opts.interval;
		pa->pq_u.codel_opts.ecn = opts->data.codel_opts.ecn;
		break;
	default:
		warnx("eval_queue_opts: unknown scheduler type %u",
		    opts->qtype);
		errors++;
		break;
	}

	return (errors);
}