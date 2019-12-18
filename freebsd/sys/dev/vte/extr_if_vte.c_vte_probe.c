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
struct vte_ident {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vte_ident* vte_find_ident (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vte_probe(device_t dev)
{
	const struct vte_ident *ident;

	ident = vte_find_ident(dev);
	if (ident != NULL) {
		device_set_desc(dev, ident->name);
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}