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
struct ifnet {scalar_t__ if_hdrlen; } ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 int /*<<< orphan*/  NET_EPOCH_WAIT () ; 
 int /*<<< orphan*/ * V_log_if ; 
 int /*<<< orphan*/ * V_pflog_if ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

__attribute__((used)) static void
ipfw_clone_destroy(struct ifnet *ifp)
{

	if (ifp->if_hdrlen == ETHER_HDR_LEN)
		V_log_if = NULL;
	else
		V_pflog_if = NULL;

	NET_EPOCH_WAIT();
	bpfdetach(ifp);
	if_detach(ifp);
	if_free(ifp);
}