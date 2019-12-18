#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_slices; int /*<<< orphan*/ * ss; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mxge_free_slice_mbufs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mxge_free_mbufs(mxge_softc_t *sc)
{
	int slice;

	for (slice = 0; slice < sc->num_slices; slice++)
		mxge_free_slice_mbufs(&sc->ss[slice]);
}