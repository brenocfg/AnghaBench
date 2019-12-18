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
struct mps_command {int cm_sglsize; void* cm_sge; TYPE_1__* cm_sc; } ;
struct TYPE_2__ {scalar_t__ reqframesz; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

void
mpi_init_sge(struct mps_command *cm, void *req, void *sge)
{
	int off, space;

	space = (int)cm->cm_sc->reqframesz;
	off = (uintptr_t)sge - (uintptr_t)req;

	KASSERT(off < space, ("bad pointers %p %p, off %d, space %d",
            req, sge, off, space));

	cm->cm_sge = sge;
	cm->cm_sglsize = space - off;
}