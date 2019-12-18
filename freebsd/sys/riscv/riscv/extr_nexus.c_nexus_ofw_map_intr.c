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
typedef  int u_int ;
struct intr_map_data_fdt {int ncells; int /*<<< orphan*/  cells; int /*<<< orphan*/  iparent; } ;
struct intr_map_data {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_MAP_DATA_FDT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ intr_alloc_map_data (int /*<<< orphan*/ ,size_t,int) ; 
 int intr_map_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct intr_map_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nexus_ofw_map_intr(device_t dev, device_t child, phandle_t iparent, int icells,
    pcell_t *intr)
{
	struct intr_map_data_fdt *fdt_data;
	size_t len;
	u_int irq;

	len = sizeof(*fdt_data) + icells * sizeof(pcell_t);
	fdt_data = (struct intr_map_data_fdt *)intr_alloc_map_data(
	    INTR_MAP_DATA_FDT, len, M_WAITOK | M_ZERO);
	fdt_data->iparent = iparent;
	fdt_data->ncells = icells;
	memcpy(fdt_data->cells, intr, icells * sizeof(pcell_t));
	irq = intr_map_irq(NULL, iparent, (struct intr_map_data *)fdt_data);

	return (irq);
}