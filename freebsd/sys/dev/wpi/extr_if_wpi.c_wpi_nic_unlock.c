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
struct wpi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_CLRBITS (struct wpi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPI_GP_CNTRL ; 
 int /*<<< orphan*/  WPI_GP_CNTRL_MAC_ACCESS_REQ ; 

__attribute__((used)) static __inline void
wpi_nic_unlock(struct wpi_softc *sc)
{
	WPI_CLRBITS(sc, WPI_GP_CNTRL, WPI_GP_CNTRL_MAC_ACCESS_REQ);
}