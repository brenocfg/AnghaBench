#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  default_classes; int /*<<< orphan*/  qpris; } ;
struct pfctl_altq {TYPE_3__ meta; } ;
struct pfctl {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ priq_opts; } ;
struct pf_altq {scalar_t__ priority; TYPE_2__ pq_u; int /*<<< orphan*/  ifname; int /*<<< orphan*/  qname; } ;

/* Variables and functions */
 scalar_t__ BIT_ISSET (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int PRCF_DEFAULTCLASS ; 
 scalar_t__ PRIQ_MAXPRI ; 
 int /*<<< orphan*/  QPRI_BITSET_SIZE ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,...) ; 

__attribute__((used)) static int
eval_pfqueue_priq(struct pfctl *pf, struct pf_altq *pa, struct pfctl_altq *if_ppa)
{

	if (pa->priority >= PRIQ_MAXPRI) {
		warnx("priority out of range: max %d", PRIQ_MAXPRI - 1);
		return (-1);
	}
	if (BIT_ISSET(QPRI_BITSET_SIZE, pa->priority, &if_ppa->meta.qpris)) {
		warnx("%s does not have a unique priority on interface %s",
		    pa->qname, pa->ifname);
		return (-1);
	} else
		BIT_SET(QPRI_BITSET_SIZE, pa->priority, &if_ppa->meta.qpris);

	if (pa->pq_u.priq_opts.flags & PRCF_DEFAULTCLASS)
		if_ppa->meta.default_classes++;
	return (0);
}