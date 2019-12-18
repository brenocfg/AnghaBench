#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* desc; } ;
struct port_info {int port_id; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct port_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 

__attribute__((used)) static int
cxgb_port_probe(device_t dev)
{
	struct port_info *p;
	char buf[80];
	const char *desc;
	
	p = device_get_softc(dev);
	desc = p->phy.desc;
	snprintf(buf, sizeof(buf), "Port %d %s", p->port_id, desc);
	device_set_desc_copy(dev, buf);
	return (0);
}