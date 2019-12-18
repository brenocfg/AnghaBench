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
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * qs; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int ctrl_xmit (struct adapter*,int /*<<< orphan*/ *,struct mbuf*) ; 

int
t3_mgmt_tx(struct adapter *adap, struct mbuf *m)
{
	return ctrl_xmit(adap, &adap->sge.qs[0], m);
}