#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_ibm_softc {int mic_led_state; int /*<<< orphan*/  handle; scalar_t__ mic_led_handle; } ;
struct TYPE_5__ {int Value; } ;
struct TYPE_7__ {TYPE_1__ Integer; int /*<<< orphan*/  Type; } ;
struct TYPE_6__ {int Count; TYPE_3__* Pointer; } ;
typedef  int ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int AcpiEvaluateObject (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int EINVAL ; 

__attribute__((used)) static int
acpi_ibm_mic_led_set (struct acpi_ibm_softc *sc, int arg)
{
	ACPI_OBJECT_LIST input;
	ACPI_OBJECT params[1];
	ACPI_STATUS status;

	if (arg < 0 || arg > 1)
		return (EINVAL);

	if (sc->mic_led_handle) {
		params[0].Type = ACPI_TYPE_INTEGER;
		params[0].Integer.Value = 0;
		/* mic led: 0 off, 2 on */
		if (arg == 1)
			params[0].Integer.Value = 2;

		input.Pointer = params;
		input.Count = 1;

		status = AcpiEvaluateObject (sc->handle, "MMTS", &input, NULL);
		if (ACPI_SUCCESS(status))
			sc->mic_led_state = arg;
		return(status);
	}

	return (0);
}