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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_TAP (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct ifnet* V_log_if ; 

void
ipfw_bpf_tap(u_char *pkt, u_int pktlen)
{
	struct ifnet *ifp = V_log_if;

	NET_EPOCH_ASSERT();
	if (ifp != NULL)
		BPF_TAP(ifp, pkt, pktlen);
}