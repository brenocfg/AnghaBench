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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct ifnet* V_log_if ; 

void
ipfw_bpf_mtap(struct mbuf *m)
{
	struct ifnet *ifp = V_log_if;

	NET_EPOCH_ASSERT();
	if (ifp != NULL)
		BPF_MTAP(ifp, m);
}