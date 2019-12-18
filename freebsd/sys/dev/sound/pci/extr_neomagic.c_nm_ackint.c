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
typedef  int u_int32_t ;
struct sc_info {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NM256AV_PCI_ID ; 
 scalar_t__ NM256ZX_PCI_ID ; 
 int /*<<< orphan*/  NM_INT_REG ; 
 int /*<<< orphan*/  nm_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nm_ackint(struct sc_info *sc, u_int32_t num)
{
	if (sc->type == NM256AV_PCI_ID) {
		nm_wr(sc, NM_INT_REG, num << 1, 2);
	} else if (sc->type == NM256ZX_PCI_ID) {
		nm_wr(sc, NM_INT_REG, num, 4);
	}
}