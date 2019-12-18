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
typedef  size_t u_int ;
struct g_concat_softc {size_t sc_ndisks; TYPE_1__* sc_disks; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d_consumer; } ;

/* Variables and functions */

__attribute__((used)) static u_int
g_concat_nvalid(struct g_concat_softc *sc)
{
	u_int i, no;

	no = 0;
	for (i = 0; i < sc->sc_ndisks; i++) {
		if (sc->sc_disks[i].d_consumer != NULL)
			no++;
	}

	return (no);
}