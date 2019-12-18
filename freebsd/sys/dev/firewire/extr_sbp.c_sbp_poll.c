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
struct TYPE_2__ {struct firewire_comm* fc; } ;
struct sbp_softc {TYPE_1__ fd; } ;
struct firewire_comm {int /*<<< orphan*/  (* poll ) (struct firewire_comm*,int /*<<< orphan*/ ,int) ;} ;
struct cam_sim {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct firewire_comm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sbp_poll(struct cam_sim *sim)
{
	struct sbp_softc *sbp;
	struct firewire_comm *fc;

	sbp = (struct sbp_softc *)sim->softc;
	fc = sbp->fd.fc;

	fc->poll(fc, 0, -1);

	return;
}