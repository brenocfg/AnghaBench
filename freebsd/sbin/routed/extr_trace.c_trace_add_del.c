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
struct rt_entry {int /*<<< orphan*/  rt_state; int /*<<< orphan*/  rt_ifp; int /*<<< orphan*/  rt_spares; int /*<<< orphan*/  rt_gate; int /*<<< orphan*/  rt_mask; int /*<<< orphan*/  rt_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_RT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftrace ; 
 int /*<<< orphan*/  lastlog () ; 
 int /*<<< orphan*/  print_rts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_bits ; 
 char* rtname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
trace_add_del(const char * action, struct rt_entry *rt)
{
	if (ftrace == NULL)
		return;

	lastlog();
	(void)fprintf(ftrace, "%s    %-35s ",
		      action,
		      rtname(rt->rt_dst, rt->rt_mask, rt->rt_gate));
	print_rts(rt->rt_spares, 0,0,0,0,AGE_RT(rt->rt_state,rt->rt_ifp));
	trace_bits(rs_bits, rt->rt_state, 0);
	(void)fputc('\n',ftrace);
}