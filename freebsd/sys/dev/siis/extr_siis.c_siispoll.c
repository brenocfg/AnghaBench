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
struct siis_channel {int /*<<< orphan*/  dev; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  siis_ch_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
siispoll(struct cam_sim *sim)
{
	struct siis_channel *ch = (struct siis_channel *)cam_sim_softc(sim);

	siis_ch_intr(ch->dev);
}