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
struct psycho_desc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psycho_compats ; 
 struct psycho_desc* psycho_find_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psycho_models ; 

__attribute__((used)) static const struct psycho_desc *
psycho_get_desc(device_t dev)
{
	const struct psycho_desc *rv;

	rv = psycho_find_desc(psycho_models, ofw_bus_get_model(dev));
	if (rv == NULL)
		rv = psycho_find_desc(psycho_compats,
		    ofw_bus_get_compat(dev));
	return (rv);
}