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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct ppc_data {struct resource* res_irq; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppc_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
#define  SYS_RES_IRQ 128 

struct resource *
ppc_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct ppc_data *ppc = DEVTOSOFTC(bus);

	switch (type) {
	case SYS_RES_IRQ:
		if (*rid == 0)
			return (ppc->res_irq);
		break;
	}
	return (NULL);
}