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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sge_wrq {int /*<<< orphan*/  eq; } ;
struct TYPE_5__ {int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_6__ {TYPE_2__ fwq; } ;
struct adapter {int /*<<< orphan*/  ctx; TYPE_3__ sge; TYPE_1__** port; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int /*<<< orphan*/  tx_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTRL_EQ_QSIZE ; 
 int /*<<< orphan*/  EQ_CTRL ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int alloc_wrq (struct adapter*,int /*<<< orphan*/ *,struct sge_wrq*,struct sysctl_oid*) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_eq (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int
alloc_ctrlq(struct adapter *sc, struct sge_wrq *ctrlq, int idx,
    struct sysctl_oid *oid)
{
	int rc;
	char name[16];
	struct sysctl_oid_list *children;

	snprintf(name, sizeof(name), "%s ctrlq%d", device_get_nameunit(sc->dev),
	    idx);
	init_eq(sc, &ctrlq->eq, EQ_CTRL, CTRL_EQ_QSIZE, sc->port[idx]->tx_chan,
	    sc->sge.fwq.cntxt_id, name);

	children = SYSCTL_CHILDREN(oid);
	snprintf(name, sizeof(name), "%d", idx);
	oid = SYSCTL_ADD_NODE(&sc->ctx, children, OID_AUTO, name, CTLFLAG_RD,
	    NULL, "ctrl queue");
	rc = alloc_wrq(sc, NULL, ctrlq, oid);

	return (rc);
}