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
typedef  int u16 ;
struct switch_port_link {int link; int duplex; int /*<<< orphan*/  speed; } ;
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_PORTREG (int /*<<< orphan*/ ,int) ; 
 int MV_PORT_STATUS_FDX ; 
 int MV_PORT_STATUS_LINK ; 
#define  MV_PORT_STATUS_SPEED_10 130 
#define  MV_PORT_STATUS_SPEED_100 129 
#define  MV_PORT_STATUS_SPEED_1000 128 
 int MV_PORT_STATUS_SPEED_MASK ; 
 int MV_PORT_STATUS_SPEED_SHIFT ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_10 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_100 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_1000 ; 
 int sr16 (struct switch_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvsw61xx_get_port_link(struct switch_dev *dev, int port,
		struct switch_port_link *link)
{
	u16 status, speed;

	status = sr16(dev, MV_PORTREG(STATUS, port));

	link->link = status & MV_PORT_STATUS_LINK;
	if (!link->link)
		return 0;

	link->duplex = status & MV_PORT_STATUS_FDX;

	speed = (status & MV_PORT_STATUS_SPEED_MASK) >>
			MV_PORT_STATUS_SPEED_SHIFT;

	switch (speed) {
	case MV_PORT_STATUS_SPEED_10:
		link->speed = SWITCH_PORT_SPEED_10;
		break;
	case MV_PORT_STATUS_SPEED_100:
		link->speed = SWITCH_PORT_SPEED_100;
		break;
	case MV_PORT_STATUS_SPEED_1000:
		link->speed = SWITCH_PORT_SPEED_1000;
		break;
	}

	return 0;
}