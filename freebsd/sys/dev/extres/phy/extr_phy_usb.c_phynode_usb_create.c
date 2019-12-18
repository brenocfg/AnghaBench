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
struct phynode_usb_sc {int /*<<< orphan*/  std_param; } ;
struct phynode_usb_init_def {int /*<<< orphan*/  std_param; int /*<<< orphan*/  phynode_init_def; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  phynode_class_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct phynode_usb_sc* phynode_get_softc (struct phynode*) ; 

struct phynode *
phynode_usb_create(device_t pdev, phynode_class_t phynode_class,
    struct phynode_usb_init_def *def)

{
	struct phynode *phynode;
	struct phynode_usb_sc *sc;

	phynode = phynode_create(pdev, phynode_class, &def->phynode_init_def);
	if (phynode == NULL)
		return (NULL);
	sc = phynode_get_softc(phynode);
	sc->std_param = def->std_param;
	return (phynode);
}