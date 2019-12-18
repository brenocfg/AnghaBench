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
struct int_nameval {int value; int /*<<< orphan*/  name; int /*<<< orphan*/  exists; } ;
struct acpi_fujitsu_softc {int bIsMuted; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; struct int_nameval rvol; struct int_nameval rbll; struct int_nameval gsif; struct int_nameval ghks; struct int_nameval gvol; struct int_nameval gmou; struct int_nameval gbls; struct int_nameval gbll; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int FALSE ; 
 int GENERAL_SETTING_BITS ; 
#define  METHOD_GBLL 136 
#define  METHOD_GBLS 135 
#define  METHOD_GHKS 134 
#define  METHOD_GMOU 133 
#define  METHOD_GSIF 132 
#define  METHOD_GVOL 131 
#define  METHOD_MUTE 130 
#define  METHOD_RBLL 129 
#define  METHOD_RVOL 128 
 int VOLUME_MUTE_BIT ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fujitsu ; 

__attribute__((used)) static int
acpi_fujitsu_method_get(struct acpi_fujitsu_softc *sc, int method)
{
	struct int_nameval	nv;
	ACPI_STATUS		status;

	ACPI_SERIAL_ASSERT(fujitsu);

	switch (method) {
		case METHOD_GBLL:
			nv = sc->gbll;
			break;
		case METHOD_GBLS:
			nv = sc->gbls;
			break;
		case METHOD_GMOU:
			nv = sc->gmou;
			break;
		case METHOD_GVOL:
		case METHOD_MUTE:
			nv = sc->gvol;
			break;
		case METHOD_GHKS:
			nv = sc->ghks;
			break;
		case METHOD_GSIF:
			nv = sc->gsif;
			break;
		case METHOD_RBLL:
			nv = sc->rbll;
			break;
		case METHOD_RVOL:
			nv = sc->rvol;
			break;
		default:
			return (FALSE);
	}

	if(!nv.exists)
		return (EINVAL);

	status = acpi_GetInteger(sc->handle, nv.name, &nv.value);
	if (ACPI_FAILURE(status)) {
		device_printf(sc->dev, "Couldn't query method (%s)\n", nv.name);
		return (FALSE);
	}

	if (method == METHOD_MUTE) {
		sc->bIsMuted = (uint8_t)((nv.value & VOLUME_MUTE_BIT) != 0);
		return (sc->bIsMuted);
	}

	nv.value &= GENERAL_SETTING_BITS;
	return (nv.value);
}