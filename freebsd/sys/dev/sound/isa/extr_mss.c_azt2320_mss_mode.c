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
struct mss_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SBDSP_CMD ; 
 int /*<<< orphan*/  SBDSP_STATUS ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int port_rd (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_wr (struct resource*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
azt2320_mss_mode(struct mss_info *mss, device_t dev)
{
	struct resource *sbport;
	int		i, ret, rid;

	rid = 0;
	ret = -1;
	sbport = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (sbport) {
		for (i = 0; i < 1000; i++) {
			if ((port_rd(sbport, SBDSP_STATUS) & 0x80))
				DELAY((i > 100) ? 1000 : 10);
			else {
				port_wr(sbport, SBDSP_CMD, 0x09);
				break;
			}
		}
		for (i = 0; i < 1000; i++) {
			if ((port_rd(sbport, SBDSP_STATUS) & 0x80))
				DELAY((i > 100) ? 1000 : 10);
			else {
				port_wr(sbport, SBDSP_CMD, 0x00);
				ret = 0;
				break;
			}
		}
		DELAY(1000);
		bus_release_resource(dev, SYS_RES_IOPORT, rid, sbport);
	}
	return ret;
}