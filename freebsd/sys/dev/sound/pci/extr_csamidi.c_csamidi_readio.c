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
typedef  scalar_t__ u_long ;
typedef  int u_int32_t ;
struct csa_midi_softc {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 scalar_t__ BA0_AC97_RESET ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
csamidi_readio(struct csa_midi_softc *scp, u_long offset)
{
	if (offset < BA0_AC97_RESET)
		return bus_space_read_4(rman_get_bustag(scp->io), rman_get_bushandle(scp->io), offset) & 0xffffffff;
	else
		return (0);
}