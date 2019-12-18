#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
#define  ENOENT 129 
#define  ENXIO 128 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_isa_ids ; 
 TYPE_1__* le_isa_params ; 
 int /*<<< orphan*/  le_isa_probe_legacy (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static int
le_isa_probe(device_t dev)
{
	int i;

	switch (ISA_PNP_PROBE(device_get_parent(dev), dev, le_isa_ids)) {
	case 0:
		return (BUS_PROBE_DEFAULT);
	case ENOENT:
		for (i = 0; i < nitems(le_isa_params); i++) {
			if (le_isa_probe_legacy(dev, &le_isa_params[i]) == 0) {
				device_set_desc(dev, le_isa_params[i].name);
				return (BUS_PROBE_DEFAULT);
			}
		}
		/* FALLTHROUGH */
	case ENXIO:
	default:
		return (ENXIO);
	}
}