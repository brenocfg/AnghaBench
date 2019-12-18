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
struct rt_spare {scalar_t__ rts_gate; scalar_t__ rts_router; scalar_t__ rts_metric; scalar_t__ rts_tag; scalar_t__ rts_de_ag; scalar_t__ rts_ifp; scalar_t__ rts_time; } ;
struct rt_entry {scalar_t__ rt_ifp; int /*<<< orphan*/  rt_state; struct rt_spare* rt_spares; int /*<<< orphan*/  rt_mask; int /*<<< orphan*/  rt_dst; } ;

/* Variables and functions */
 scalar_t__ AGE_RT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RIP_DEFAULT ; 
 int /*<<< orphan*/  TRACEACTIONS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftrace ; 
 int /*<<< orphan*/  lastlog () ; 
 char* naddr_ntoa (scalar_t__) ; 
 int /*<<< orphan*/  print_rts (struct rt_spare*,int,int,int,int,int) ; 
 char* rtname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
trace_upslot(struct rt_entry *rt,
	     struct rt_spare *rts,
	     struct rt_spare *new)
{
	if (!TRACEACTIONS || ftrace == NULL)
		return;

	if (rts->rts_gate == new->rts_gate
	    && rts->rts_router == new->rts_router
	    && rts->rts_metric == new->rts_metric
	    && rts->rts_tag == new->rts_tag
	    && rts->rts_de_ag == new->rts_de_ag)
		return;

	lastlog();
	if (new->rts_gate == 0) {
		(void)fprintf(ftrace, "Del #%d %-35s ",
			      (int)(rts - rt->rt_spares),
			      rtname(rt->rt_dst, rt->rt_mask, rts->rts_gate));
		print_rts(rts, 0,0,0,0,
			  (rts != rt->rt_spares
			   || AGE_RT(rt->rt_state,new->rts_ifp)));

	} else if (rts->rts_gate != RIP_DEFAULT) {
		(void)fprintf(ftrace, "Chg #%d %-35s ",
			      (int)(rts - rt->rt_spares),
			      rtname(rt->rt_dst, rt->rt_mask, rts->rts_gate));
		print_rts(rts, 0,0,
			  rts->rts_gate != new->rts_gate,
			  rts->rts_tag != new->rts_tag,
			  rts != rt->rt_spares || AGE_RT(rt->rt_state,
							rt->rt_ifp));

		(void)fprintf(ftrace, "\n       %19s%-16s ", "",
			      (new->rts_gate != rts->rts_gate
			       ? naddr_ntoa(new->rts_gate) : ""));
		print_rts(new,
			  -(new->rts_metric == rts->rts_metric),
			  -(new->rts_ifp == rts->rts_ifp),
			  0,
			  rts->rts_tag != new->rts_tag,
			  (new->rts_time != rts->rts_time
			   && (rts != rt->rt_spares
			       || AGE_RT(rt->rt_state, new->rts_ifp))));

	} else {
		(void)fprintf(ftrace, "Add #%d %-35s ",
			      (int)(rts - rt->rt_spares),
			      rtname(rt->rt_dst, rt->rt_mask, new->rts_gate));
		print_rts(new, 0,0,0,0,
			  (rts != rt->rt_spares
			   || AGE_RT(rt->rt_state,new->rts_ifp)));
	}
	(void)fputc('\n',ftrace);
}