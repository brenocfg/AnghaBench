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
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;
struct bnxt_softc {int /*<<< orphan*/  def_cp_task; TYPE_1__ def_cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CP_DISABLE_DB (int /*<<< orphan*/ *) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnxt_handle_def_cp(void *arg)
{
	struct bnxt_softc *softc = arg;

	BNXT_CP_DISABLE_DB(&softc->def_cp_ring.ring);
	GROUPTASK_ENQUEUE(&softc->def_cp_task);
	return FILTER_HANDLED;
}