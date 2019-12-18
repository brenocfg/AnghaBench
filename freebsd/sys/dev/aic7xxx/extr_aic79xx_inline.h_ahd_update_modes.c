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
struct ahd_softc {int dummy; } ;
typedef  int ahd_mode_state ;
typedef  int /*<<< orphan*/  ahd_mode ;

/* Variables and functions */
 int AHD_SHOW_MODEPTR ; 
 int /*<<< orphan*/  MODE_PTR ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_extract_mode_state (struct ahd_softc*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_known_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static __inline void
ahd_update_modes(struct ahd_softc *ahd)
{
	ahd_mode_state mode_ptr;
	ahd_mode src;
	ahd_mode dst;

	mode_ptr = ahd_inb(ahd, MODE_PTR);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MODEPTR) != 0)
		printf("Reading mode 0x%x\n", mode_ptr);
#endif
	ahd_extract_mode_state(ahd, mode_ptr, &src, &dst);
	ahd_known_modes(ahd, src, dst);
}