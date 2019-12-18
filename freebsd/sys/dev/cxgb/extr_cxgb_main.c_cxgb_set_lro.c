#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enabled; } ;
struct sge_qset {TYPE_2__ lro; } ;
struct port_info {int nqsets; int first_qset; struct adapter* adapter; } ;
struct TYPE_3__ {struct sge_qset* qs; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */

__attribute__((used)) static int
cxgb_set_lro(struct port_info *p, int enabled)
{
	int i;
	struct adapter *adp = p->adapter;
	struct sge_qset *q;

	for (i = 0; i < p->nqsets; i++) {
		q = &adp->sge.qs[p->first_qset + i];
		q->lro.enabled = (enabled != 0);
	}
	return (0);
}