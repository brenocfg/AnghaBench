#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sfxge_softc {int dummy; } ;
struct TYPE_6__ {int op; } ;
typedef  TYPE_1__ sfxge_ioc_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SFXGE_MCDI_IOC 130 
#define  SFXGE_NVRAM_IOC 129 
#define  SFXGE_VPD_IOC 128 
 int sfxge_mcdi_ioctl (struct sfxge_softc*,TYPE_1__*) ; 
 int sfxge_nvram_ioctl (struct sfxge_softc*,TYPE_1__*) ; 
 int sfxge_vpd_ioctl (struct sfxge_softc*,TYPE_1__*) ; 

__attribute__((used)) static int
sfxge_private_ioctl(struct sfxge_softc *sc, sfxge_ioc_t *ioc)
{
	switch (ioc->op) {
	case SFXGE_MCDI_IOC:
		return (sfxge_mcdi_ioctl(sc, ioc));
	case SFXGE_NVRAM_IOC:
		return (sfxge_nvram_ioctl(sc, ioc));
	case SFXGE_VPD_IOC:
		return (sfxge_vpd_ioctl(sc, ioc));
	default:
		return (EOPNOTSUPP);
	}
}