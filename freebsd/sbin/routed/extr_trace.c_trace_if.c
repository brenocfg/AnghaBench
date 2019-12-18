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
struct interface {char* int_name; int int_if_flags; int int_metric; int int_adj_inmetric; int int_adj_outmetric; int int_state; int int_d_metric; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  int_net; int /*<<< orphan*/  int_dstaddr; int /*<<< orphan*/  int_addr; } ;

/* Variables and functions */
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IS_RIP_OUT_OFF (int) ; 
 int /*<<< orphan*/  TRACEACTIONS ; 
 char* addrname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftrace ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_bits ; 
 int /*<<< orphan*/  is_bits ; 
 int /*<<< orphan*/  lastlog () ; 
 char* naddr_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
trace_if(const char *act,
	 struct interface *ifp)
{
	if (!TRACEACTIONS || ftrace == NULL)
		return;

	lastlog();
	(void)fprintf(ftrace, "%-3s interface %-4s ", act, ifp->int_name);
	(void)fprintf(ftrace, "%-15s-->%-15s ",
		      naddr_ntoa(ifp->int_addr),
		      addrname(((ifp->int_if_flags & IFF_POINTOPOINT)
				? ifp->int_dstaddr
				: htonl(ifp->int_net)),
			       ifp->int_mask, 1));
	if (ifp->int_metric != 0)
		(void)fprintf(ftrace, "metric=%d ", ifp->int_metric);
	if (ifp->int_adj_inmetric != 0)
		(void)fprintf(ftrace, "adj_inmetric=%u ",
			      ifp->int_adj_inmetric);
	if (ifp->int_adj_outmetric != 0)
		(void)fprintf(ftrace, "adj_outmetric=%u ",
			      ifp->int_adj_outmetric);
	if (!IS_RIP_OUT_OFF(ifp->int_state)
	    && ifp->int_d_metric != 0)
		(void)fprintf(ftrace, "fake_default=%u ", ifp->int_d_metric);
	trace_bits(if_bits, ifp->int_if_flags, 0);
	trace_bits(is_bits, ifp->int_state, 0);
	(void)fputc('\n',ftrace);
}