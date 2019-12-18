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
struct ifnet {int /*<<< orphan*/  if_snd; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 

int
if_sendq_prepend(if_t ifp, struct mbuf *m)
{
	IFQ_DRV_PREPEND(&((struct ifnet *)ifp)->if_snd, m);
	return (0);
}