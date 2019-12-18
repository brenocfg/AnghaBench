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
struct TYPE_2__ {scalar_t__ contender; scalar_t__ link_active; } ;
union fw_self_id {TYPE_1__ p0; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_device {int dst; int maxrec; int /*<<< orphan*/  status; scalar_t__ speed; struct firewire_comm* fc; } ;
struct firewire_comm {int max_node; int nodeid; size_t max_hop; int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  fwdev ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MGR_ID ; 
 int CSRARC (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FWDEVINIT ; 
 size_t MAX_GAPHOP ; 
 int STATE_SET ; 
 int /*<<< orphan*/  bzero (struct fw_device*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fw_asy_callback_free ; 
 union fw_self_id* fw_find_self_id (struct firewire_comm*,int) ; 
 int /*<<< orphan*/  fw_phy_config (struct firewire_comm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwmem_write_quad (struct fw_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gap_cnt ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static int
fw_bmr(struct firewire_comm *fc)
{
	struct fw_device fwdev;
	union fw_self_id *self_id;
	int cmstr;
	uint32_t quad;

	/* Check to see if the current root node is cycle master capable */
	self_id = fw_find_self_id(fc, fc->max_node);
	if (fc->max_node > 0) {
		/* XXX check cmc bit of businfo block rather than contender */
		if (self_id->p0.link_active && self_id->p0.contender)
			cmstr = fc->max_node;
		else {
			device_printf(fc->bdev,
			    "root node is not cycle master capable\n");
			/* XXX shall we be the cycle master? */
			cmstr = fc->nodeid;
			/* XXX need bus reset */
		}
	} else
		cmstr = -1;

	device_printf(fc->bdev, "bus manager %d %s\n",
		CSRARC(fc, BUS_MGR_ID),
		(CSRARC(fc, BUS_MGR_ID) != fc->nodeid) ? "(me)" : "");
	if (CSRARC(fc, BUS_MGR_ID) != fc->nodeid) {
		/* We are not the bus manager */
		return (0);
	}

	/* Optimize gapcount */
	if (fc->max_hop <= MAX_GAPHOP)
		fw_phy_config(fc, cmstr, gap_cnt[fc->max_hop]);
	/* If we are the cycle master, nothing to do */
	if (cmstr == fc->nodeid || cmstr == -1)
		return 0;
	/* Bus probe has not finished, make dummy fwdev for cmstr */
	bzero(&fwdev, sizeof(fwdev));
	fwdev.fc = fc;
	fwdev.dst = cmstr;
	fwdev.speed = 0;
	fwdev.maxrec = 8; /* 512 */
	fwdev.status = FWDEVINIT;
	/* Set cmstr bit on the cycle master */
	quad = htonl(1 << 8);
	fwmem_write_quad(&fwdev, NULL, 0/*spd*/,
	    0xffff, 0xf0000000 | STATE_SET, &quad, fw_asy_callback_free);

	return 0;
}