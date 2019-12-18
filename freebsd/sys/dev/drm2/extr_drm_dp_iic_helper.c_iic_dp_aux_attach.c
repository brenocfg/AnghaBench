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
struct iic_dp_aux_data {int /*<<< orphan*/ * port; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct iic_dp_aux_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iic_dp_aux_attach(device_t idev)
{
	struct iic_dp_aux_data *aux_data;

	aux_data = device_get_softc(idev);
	aux_data->port = device_add_child(idev, "iicbus", -1);
	if (aux_data->port == NULL)
		return (ENXIO);
	device_quiet(aux_data->port);
	bus_generic_attach(idev);
	return (0);
}