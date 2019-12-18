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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_pcie2_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

void
bhnd_pcie2_write_proto_reg(struct bhnd_pcie2_softc *sc, uint32_t addr,
    uint32_t val)
{
	// TODO
	panic("unimplemented");
}