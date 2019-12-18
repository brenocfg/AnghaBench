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
struct ecore_mcast_ramrod_params {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ecore_mcast_revert_e1h(struct bxe_softc *sc,
				       struct ecore_mcast_ramrod_params *p,
				       int old_num_bins)
{
	/* Do nothing */
}