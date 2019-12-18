#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct acpi_asus_softc {int s_brn; int s_disp; int s_lcd; int s_cam; int s_crd; int s_wlan; TYPE_2__* model; int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {int Length; TYPE_4__* Pointer; } ;
struct TYPE_8__ {int Value; } ;
struct TYPE_11__ {void* Type; TYPE_1__ Integer; } ;
struct TYPE_10__ {int Count; TYPE_4__* Pointer; } ;
struct TYPE_9__ {int /*<<< orphan*/  wlan_get; int /*<<< orphan*/  crd_get; int /*<<< orphan*/  cam_get; int /*<<< orphan*/  lcd_get; int /*<<< orphan*/  name; int /*<<< orphan*/  disp_get; int /*<<< orphan*/  brn_dn; int /*<<< orphan*/  brn_up; int /*<<< orphan*/  brn_get; } ;
typedef  int /*<<< orphan*/  Obj ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT_LIST ;
typedef  TYPE_4__ ACPI_OBJECT ;
typedef  TYPE_5__ ACPI_BUFFER ;

/* Variables and functions */
#define  ACPI_ASUS_METHOD_BRN 133 
#define  ACPI_ASUS_METHOD_CAMERA 132 
#define  ACPI_ASUS_METHOD_CARDRD 131 
#define  ACPI_ASUS_METHOD_DISP 130 
#define  ACPI_ASUS_METHOD_LCD 129 
#define  ACPI_ASUS_METHOD_WLAN 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__*) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
acpi_asus_sysctl_init(struct acpi_asus_softc *sc, int method)
{
	ACPI_STATUS	status;

	switch (method) {
	case ACPI_ASUS_METHOD_BRN:
		if (sc->model->brn_get) {
			/* GPLV/SPLV models */
			status = acpi_GetInteger(sc->handle,
			    sc->model->brn_get, &sc->s_brn);
			if (ACPI_SUCCESS(status))
				return (TRUE);
		} else if (sc->model->brn_up) {
			/* Relative models */
			status = AcpiEvaluateObject(sc->handle,
			    sc->model->brn_up, NULL, NULL);
			if (ACPI_FAILURE(status))
				return (FALSE);

			status = AcpiEvaluateObject(sc->handle,
			    sc->model->brn_dn, NULL, NULL);
			if (ACPI_FAILURE(status))
				return (FALSE);

			return (TRUE);
		}
		return (FALSE);
	case ACPI_ASUS_METHOD_DISP:
		if (sc->model->disp_get) {
			status = acpi_GetInteger(sc->handle,
			    sc->model->disp_get, &sc->s_disp);
			if (ACPI_SUCCESS(status))
				return (TRUE);
		}
		return (FALSE);
	case ACPI_ASUS_METHOD_LCD:
		if (sc->model->lcd_get) {
			if (strncmp(sc->model->name, "L3H", 3) == 0) {
				ACPI_BUFFER		Buf;
				ACPI_OBJECT		Arg[2], Obj;
				ACPI_OBJECT_LIST	Args;

				/* L3H is a bit special */
				Arg[0].Type = ACPI_TYPE_INTEGER;
				Arg[0].Integer.Value = 0x02;
				Arg[1].Type = ACPI_TYPE_INTEGER;
				Arg[1].Integer.Value = 0x03;

				Args.Count = 2;
				Args.Pointer = Arg;

				Buf.Length = sizeof(Obj);
				Buf.Pointer = &Obj;

				status = AcpiEvaluateObject(sc->handle,
				    sc->model->lcd_get, &Args, &Buf);
				if (ACPI_SUCCESS(status) &&
				    Obj.Type == ACPI_TYPE_INTEGER) {
					sc->s_lcd = Obj.Integer.Value >> 8;
					return (TRUE);
				}
			} else {
				status = acpi_GetInteger(sc->handle,
				    sc->model->lcd_get, &sc->s_lcd);
				if (ACPI_SUCCESS(status))
					return (TRUE);
			}
		}
		return (FALSE);
	case ACPI_ASUS_METHOD_CAMERA:
		if (sc->model->cam_get) {
			status = acpi_GetInteger(sc->handle,
			    sc->model->cam_get, &sc->s_cam);
			if (ACPI_SUCCESS(status))
				return (TRUE);
		}
		return (FALSE);
	case ACPI_ASUS_METHOD_CARDRD:
		if (sc->model->crd_get) {
			status = acpi_GetInteger(sc->handle,
			    sc->model->crd_get, &sc->s_crd);
			if (ACPI_SUCCESS(status))
				return (TRUE);
		}
		return (FALSE);
	case ACPI_ASUS_METHOD_WLAN:
		if (sc->model->wlan_get) {
			status = acpi_GetInteger(sc->handle,
			    sc->model->wlan_get, &sc->s_wlan);
			if (ACPI_SUCCESS(status))
				return (TRUE);
		}
		return (FALSE);
	}
	return (FALSE);
}