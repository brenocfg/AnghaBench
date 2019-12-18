#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct port_info {int nqsets; } ;
struct TYPE_8__ {int /*<<< orphan*/ * qset; } ;
struct TYPE_9__ {scalar_t__ rev; int nports; TYPE_1__ sge; } ;
struct TYPE_10__ {int flags; int nqsets; int /*<<< orphan*/  dev; TYPE_2__ params; struct port_info* port; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_TXQ_PER_SET ; 
 int USING_MSI ; 
 int USING_MSIX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  t3_free_sge_resources (TYPE_3__*,int) ; 
 int t3_sge_alloc (TYPE_3__*) ; 
 int t3_sge_alloc_qset (TYPE_3__*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct port_info*) ; 

__attribute__((used)) static int
setup_sge_qsets(adapter_t *sc)
{
	int i, j, err, irq_idx = 0, qset_idx = 0;
	u_int ntxq = SGE_TXQ_PER_SET;

	if ((err = t3_sge_alloc(sc)) != 0) {
		device_printf(sc->dev, "t3_sge_alloc returned %d\n", err);
		return (err);
	}

	if (sc->params.rev > 0 && !(sc->flags & USING_MSI))
		irq_idx = -1;

	for (i = 0; i < (sc)->params.nports; i++) {
		struct port_info *pi = &sc->port[i];

		for (j = 0; j < pi->nqsets; j++, qset_idx++) {
			err = t3_sge_alloc_qset(sc, qset_idx, (sc)->params.nports,
			    (sc->flags & USING_MSIX) ? qset_idx + 1 : irq_idx,
			    &sc->params.sge.qset[qset_idx], ntxq, pi);
			if (err) {
				t3_free_sge_resources(sc, qset_idx);
				device_printf(sc->dev,
				    "t3_sge_alloc_qset failed with %d\n", err);
				return (err);
			}
		}
	}

	sc->nqsets = qset_idx;

	return (0);
}