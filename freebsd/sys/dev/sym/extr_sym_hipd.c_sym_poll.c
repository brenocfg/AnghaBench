#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  sym_intr1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_poll(struct cam_sim *sim)
{
	sym_intr1(cam_sim_softc(sim));
}