#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** io; int /*<<< orphan*/ ** io_rid; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_releaseresource (TYPE_1__*) ; 

__attribute__((used)) static void
rp_pcireleaseresource(CONTROLLER_t *ctlp)
{
	rp_releaseresource(ctlp);
	if (ctlp->io != NULL) {
		if (ctlp->io[0] != NULL)
			bus_release_resource(ctlp->dev, SYS_RES_IOPORT, ctlp->io_rid[0], ctlp->io[0]);
		free(ctlp->io, M_DEVBUF);
		ctlp->io = NULL;
	}
	if (ctlp->io_rid != NULL) {
		free(ctlp->io_rid, M_DEVBUF);
		ctlp->io = NULL;
	}
}