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
struct iwn_softc {scalar_t__ hw_type; } ;

/* Variables and functions */
 scalar_t__ IWN_HW_REV_TYPE_5300 ; 

__attribute__((used)) static int
iwn_is_3stream_device(struct iwn_softc *sc)
{
	/* XXX for now only 5300, until the 5350 can be tested */
	if (sc->hw_type == IWN_HW_REV_TYPE_5300)
		return (1);
	return (0);
}