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
struct ahd_softc {scalar_t__ src_mode; scalar_t__ dst_mode; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 scalar_t__ AHD_MODE_UNKNOWN ; 
 int /*<<< orphan*/  ahd_build_mode_state (struct ahd_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_update_modes (struct ahd_softc*) ; 

__attribute__((used)) static __inline ahd_mode_state
ahd_save_modes(struct ahd_softc *ahd)
{
	if (ahd->src_mode == AHD_MODE_UNKNOWN
	 || ahd->dst_mode == AHD_MODE_UNKNOWN)
		ahd_update_modes(ahd);

	return (ahd_build_mode_state(ahd, ahd->src_mode, ahd->dst_mode));
}