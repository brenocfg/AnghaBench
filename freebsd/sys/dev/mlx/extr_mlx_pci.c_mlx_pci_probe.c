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
struct mlx_ident {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx_ident* mlx_pci_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx_pci_probe(device_t dev)
{
    struct mlx_ident	*m;

    debug_called(1);

    m = mlx_pci_match(dev);
    if (m != NULL) {
	device_set_desc(dev, m->desc);
	return(BUS_PROBE_DEFAULT);
    }
    return(ENXIO);
}