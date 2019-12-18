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
typedef  int /*<<< orphan*/  uint32_t ;
struct hdaa_widget {scalar_t__ enable; int /*<<< orphan*/  nid; TYPE_1__* devinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * HDA_COLORS ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_ASSOCIATION (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_COLOR (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTIVITY (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_DEVICE (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_MISC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_SEQUENCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HDA_CONNECTORS ; 
 int /*<<< orphan*/ * HDA_CONNS ; 
 int /*<<< orphan*/ * HDA_DEVS ; 
 int /*<<< orphan*/ * HDA_LOCS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
hdaa_dump_pin_config(struct hdaa_widget *w, uint32_t conf)
{

	device_printf(w->devinfo->dev, "%2d %08x %-2d %-2d "
	    "%-13s %-5s %-7s %-10s %-7s %d%s\n",
	    w->nid, conf,
	    HDA_CONFIG_DEFAULTCONF_ASSOCIATION(conf),
	    HDA_CONFIG_DEFAULTCONF_SEQUENCE(conf),
	    HDA_DEVS[HDA_CONFIG_DEFAULTCONF_DEVICE(conf)],
	    HDA_CONNS[HDA_CONFIG_DEFAULTCONF_CONNECTIVITY(conf)],
	    HDA_CONNECTORS[HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE(conf)],
	    HDA_LOCS[HDA_CONFIG_DEFAULTCONF_LOCATION(conf)],
	    HDA_COLORS[HDA_CONFIG_DEFAULTCONF_COLOR(conf)],
	    HDA_CONFIG_DEFAULTCONF_MISC(conf),
	    (w->enable == 0)?" DISA":"");
}