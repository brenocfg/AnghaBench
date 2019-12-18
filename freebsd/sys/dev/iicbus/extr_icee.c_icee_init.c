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
struct icee_softc {int /*<<< orphan*/  wr_sz; int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (char const*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
icee_init(struct icee_softc *sc)
{
	const char *dname;
	int dunit;

	dname = device_get_name(sc->dev);
	dunit = device_get_unit(sc->dev);
	resource_int_value(dname, dunit, "size", &sc->size);
	resource_int_value(dname, dunit, "type", &sc->type);
	resource_int_value(dname, dunit, "wr_sz", &sc->wr_sz);
}