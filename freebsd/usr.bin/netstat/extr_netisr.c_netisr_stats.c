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
typedef  size_t u_int ;
struct sysctl_netisr_workstream {int dummy; } ;
struct sysctl_netisr_proto {int dummy; } ;

/* Variables and functions */
 scalar_t__ bindthreads ; 
 int /*<<< orphan*/  defaultqlimit ; 
 int /*<<< orphan*/  dispatch_policy ; 
 scalar_t__ live ; 
 int /*<<< orphan*/  maxqlimit ; 
 int /*<<< orphan*/  maxthreads ; 
 int /*<<< orphan*/  netisr_load_kvm_config () ; 
 int /*<<< orphan*/  netisr_load_kvm_proto () ; 
 int /*<<< orphan*/  netisr_load_kvm_workstream () ; 
 int /*<<< orphan*/  netisr_load_sysctl_config () ; 
 int /*<<< orphan*/  netisr_load_sysctl_proto () ; 
 int /*<<< orphan*/  netisr_load_sysctl_work () ; 
 int /*<<< orphan*/  netisr_load_sysctl_workstream () ; 
 int /*<<< orphan*/  netisr_print_proto (struct sysctl_netisr_proto*) ; 
 int /*<<< orphan*/  netisr_print_workstream (struct sysctl_netisr_workstream*) ; 
 int /*<<< orphan*/  numthreads ; 
 struct sysctl_netisr_proto* proto_array ; 
 size_t proto_array_len ; 
 struct sysctl_netisr_workstream* workstream_array ; 
 size_t workstream_array_len ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
netisr_stats(void)
{
	struct sysctl_netisr_workstream *snwsp;
	struct sysctl_netisr_proto *snpp;
	u_int i;

	if (live) {
		netisr_load_sysctl_config();
		netisr_load_sysctl_proto();
		netisr_load_sysctl_workstream();
		netisr_load_sysctl_work();
	} else {
		netisr_load_kvm_config();
		netisr_load_kvm_proto();
		netisr_load_kvm_workstream();		/* Also does work. */
	}

	xo_open_container("netisr");

	xo_emit("{T:Configuration}:\n");
	xo_emit("{T:/%-25s} {T:/%12s} {T:/%12s}\n",
	    "Setting", "Current", "Limit");
	xo_emit("{T:/%-25s} {T:/%12u} {T:/%12u}\n",
	    "Thread count", numthreads, maxthreads);
	xo_emit("{T:/%-25s} {T:/%12u} {T:/%12u}\n",
	    "Default queue limit", defaultqlimit, maxqlimit);
	xo_emit("{T:/%-25s} {T:/%12s} {T:/%12s}\n",
	    "Dispatch policy", dispatch_policy, "n/a");
	xo_emit("{T:/%-25s} {T:/%12s} {T:/%12s}\n",
	    "Threads bound to CPUs", bindthreads ? "enabled" : "disabled",
	    "n/a");
	xo_emit("\n");

	xo_emit("{T:Protocols}:\n");
	xo_emit("{T:/%-6s} {T:/%5s} {T:/%6s} {T:/%-6s} {T:/%-8s} {T:/%-5s}\n",
	    "Name", "Proto", "QLimit", "Policy", "Dispatch", "Flags");
	xo_open_list("protocol");
	for (i = 0; i < proto_array_len; i++) {
		xo_open_instance("protocol");
		snpp = &proto_array[i];
		netisr_print_proto(snpp);
		xo_close_instance("protocol");
	}
	xo_close_list("protocol");
	xo_emit("\n");

	xo_emit("{T:Workstreams}:\n");
	xo_emit("{T:/%4s} {T:/%3s} ", "WSID", "CPU");
	xo_emit("{P:/%2s}", "");
	xo_emit("{T:/%-6s} {T:/%5s} {T:/%5s} {T:/%8s} {T:/%8s} {T:/%8s} "
	    "{T:/%8s} {T:/%8s}\n",
	    "Name", "Len", "WMark", "Disp'd", "HDisp'd", "QDrops", "Queued",
	    "Handled");
	xo_open_list("workstream");
	for (i = 0; i < workstream_array_len; i++) {
		xo_open_instance("workstream");
		snwsp = &workstream_array[i];
		netisr_print_workstream(snwsp);
		xo_close_instance("workstream");
	}
	xo_close_list("workstream");
	xo_close_container("netisr");
}