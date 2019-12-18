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
struct rp_port {TYPE_1__* rp_ctlp; } ;
struct TYPE_2__ {int /*<<< orphan*/  free; } ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
rpfree(void *softc)
{
	struct	rp_port *rp = softc;
	CONTROLLER_t *ctlp = rp->rp_ctlp;

	atomic_subtract_32(&ctlp->free, 1);
}