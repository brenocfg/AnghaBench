#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct aibs_softc {int /*<<< orphan*/  sc_dev; scalar_t__ sc_ggrp_method; } ;
struct aibs_sensor {int t; int /*<<< orphan*/  i; int /*<<< orphan*/  l; int /*<<< orphan*/  h; } ;
struct TYPE_10__ {int Count; TYPE_3__* Elements; } ;
struct TYPE_11__ {scalar_t__ Type; TYPE_4__ Package; } ;
struct TYPE_8__ {int /*<<< orphan*/  Value; } ;
struct TYPE_7__ {char* Pointer; } ;
struct TYPE_9__ {scalar_t__ Type; TYPE_2__ Integer; TYPE_1__ String; } ;
typedef  TYPE_5__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int AIBS_SENS_TYPE (int /*<<< orphan*/ ) ; 
#define  AIBS_SENS_TYPE_FAN 130 
#define  AIBS_SENS_TYPE_TEMP 129 
#define  AIBS_SENS_TYPE_VOLT 128 
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
aibs_add_sensor(struct aibs_softc *sc, ACPI_OBJECT *o,
    struct aibs_sensor* sensor, const char ** descr)
{
	int		off;

	/*
	 * Packages for the old and new methods are quite
	 * similar except that the new package has two
	 * new (unknown / unused) fields after the name field.
	 */
	if (sc->sc_ggrp_method)
		off = 4;
	else
		off = 2;

	if (o->Type != ACPI_TYPE_PACKAGE) {
		device_printf(sc->sc_dev,
		    "sensor object is not a package: %i type\n",
		     o->Type);
		return (ENXIO);
	}
	if (o[0].Package.Count != (off + 3) ||
	    o->Package.Elements[0].Type != ACPI_TYPE_INTEGER ||
	    o->Package.Elements[1].Type != ACPI_TYPE_STRING ||
	    o->Package.Elements[off].Type != ACPI_TYPE_INTEGER ||
	    o->Package.Elements[off + 1].Type != ACPI_TYPE_INTEGER ||
	    o->Package.Elements[off + 2].Type != ACPI_TYPE_INTEGER) {
		device_printf(sc->sc_dev, "unexpected package content\n");
		return (ENXIO);
	}

	sensor->i = o->Package.Elements[0].Integer.Value;
	*descr = o->Package.Elements[1].String.Pointer;
	sensor->l = o->Package.Elements[off].Integer.Value;
	sensor->h = o->Package.Elements[off + 1].Integer.Value;
	/* For the new method the second value is a range size. */
	if (sc->sc_ggrp_method)
		sensor->h += sensor->l;
	sensor->t = AIBS_SENS_TYPE(sensor->i);

	switch (sensor->t) {
	case AIBS_SENS_TYPE_VOLT:
	case AIBS_SENS_TYPE_TEMP:
	case AIBS_SENS_TYPE_FAN:
		return (0);
	default:
		device_printf(sc->sc_dev, "unknown sensor type 0x%x",
		    sensor->t);
		return (ENXIO);
	}
}