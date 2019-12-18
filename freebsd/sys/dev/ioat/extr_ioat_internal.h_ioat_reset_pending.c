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
typedef  int uint8_t ;
struct ioat_softc {int dummy; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHANCMD_OFFSET ; 
 int IOAT_CHANCMD_RESET ; 
 int ioat_read_1 (struct ioat_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline boolean_t
ioat_reset_pending(struct ioat_softc *ioat)
{
	uint8_t cmd;

	cmd = ioat_read_1(ioat, IOAT_CHANCMD_OFFSET);
	return ((cmd & IOAT_CHANCMD_RESET) != 0);
}