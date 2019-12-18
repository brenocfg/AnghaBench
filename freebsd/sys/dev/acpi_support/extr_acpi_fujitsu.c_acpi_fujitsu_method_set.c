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
struct int_nameval {int value; int /*<<< orphan*/  exists; } ;
struct acpi_fujitsu_softc {int lastValChanged; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; struct int_nameval gvol; struct int_nameval gmou; struct int_nameval gbls; struct int_nameval gbll; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int BRIGHT_CHANGED ; 
 int EINVAL ; 
 int FALSE ; 
#define  METHOD_GBLL 132 
#define  METHOD_GBLS 131 
#define  METHOD_GMOU 130 
#define  METHOD_GVOL 129 
#define  METHOD_MUTE 128 
 int MOUSE_CHANGED ; 
 int VOLUME_CHANGED ; 
 int VOLUME_MUTE_BIT ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fujitsu ; 

__attribute__((used)) static int
acpi_fujitsu_method_set(struct acpi_fujitsu_softc *sc, int method, int value)
{
	struct int_nameval	nv;
	ACPI_STATUS		status;
	char			*control;
	int			changed;

	ACPI_SERIAL_ASSERT(fujitsu);

	switch (method) {
		case METHOD_GBLL:
			changed = BRIGHT_CHANGED;
			control = "SBLL";
			nv = sc->gbll;
			break;
		case METHOD_GBLS:
			changed = BRIGHT_CHANGED;
			control = "SBL2";
			nv = sc->gbls;
			break;
		case METHOD_GMOU:
			changed = MOUSE_CHANGED;
			control = "SMOU";
			nv = sc->gmou;
			break;
		case METHOD_GVOL:
		case METHOD_MUTE:
			changed = VOLUME_CHANGED;
			control = "SVOL";
			nv = sc->gvol;
			break;
		default:
			return (EINVAL);
	}

	if(!nv.exists)
		return (EINVAL);

	if (method == METHOD_MUTE) {
		if (value == 1)
			value = nv.value | VOLUME_MUTE_BIT;
		else if (value == 0)
			value = nv.value & ~VOLUME_MUTE_BIT;
		else
			return (EINVAL);
	}

	status = acpi_SetInteger(sc->handle, control, value);
	if (ACPI_FAILURE(status)) {
		device_printf(sc->dev, "Couldn't update %s\n", control);
		return (FALSE);
	}

	sc->lastValChanged = changed;
	return (0);
}