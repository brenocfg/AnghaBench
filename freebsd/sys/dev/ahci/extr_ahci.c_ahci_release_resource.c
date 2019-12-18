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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_IRQ_RID ; 
 int EINVAL ; 
 int ENOENT ; 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 

int
ahci_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{

	switch (type) {
	case SYS_RES_MEMORY:
		rman_release_resource(r);
		return (0);
	case SYS_RES_IRQ:
		if (rid != ATA_IRQ_RID)
			return (ENOENT);
		return (0);
	}
	return (EINVAL);
}