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
typedef  int uint8_t ;
struct bcma_erom {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
#define  BCMA_EROM_REGION_TYPE_BRIDGE 131 
#define  BCMA_EROM_REGION_TYPE_DEVICE 130 
#define  BCMA_EROM_REGION_TYPE_MWRAP 129 
#define  BCMA_EROM_REGION_TYPE_SWRAP 128 
 int /*<<< orphan*/  BHND_PORT_AGENT ; 
 int /*<<< orphan*/  BHND_PORT_BRIDGE ; 
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  EROM_LOG (struct bcma_erom*,char*,int) ; 

__attribute__((used)) static int
bcma_erom_region_to_port_type(struct bcma_erom *erom, uint8_t region_type,
    bhnd_port_type *port_type)
{
	switch (region_type) {
	case BCMA_EROM_REGION_TYPE_DEVICE:
		*port_type = BHND_PORT_DEVICE;
		return (0);
	case BCMA_EROM_REGION_TYPE_BRIDGE:
		*port_type = BHND_PORT_BRIDGE;
		return (0);
	case BCMA_EROM_REGION_TYPE_MWRAP:
	case BCMA_EROM_REGION_TYPE_SWRAP:
		*port_type = BHND_PORT_AGENT;
		return (0);
	default:
		EROM_LOG(erom, "unsupported region type %hhx\n",
			region_type);
		return (EINVAL);
	}
}