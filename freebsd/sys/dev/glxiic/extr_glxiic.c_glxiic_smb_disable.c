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
typedef  int uint16_t ;
struct glxiic_softc {int /*<<< orphan*/  smb_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_SMB_CTRL2 ; 
 int GLXIIC_SMB_CTRL2_EN_BIT ; 
 int bus_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
glxiic_smb_disable(struct glxiic_softc *sc)
{
	uint16_t sclfrq;

	sclfrq = bus_read_2(sc->smb_res, GLXIIC_SMB_CTRL2);
	bus_write_2(sc->smb_res, GLXIIC_SMB_CTRL2,
	    sclfrq & ~GLXIIC_SMB_CTRL2_EN_BIT);
}