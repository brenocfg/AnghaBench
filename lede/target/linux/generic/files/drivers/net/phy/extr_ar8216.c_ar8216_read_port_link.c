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
typedef  int u32 ;
struct switch_port_link {int aneg; int link; int duplex; int tx_flow; int rx_flow; int /*<<< orphan*/  speed; int /*<<< orphan*/  eee; } ;
struct ar8xxx_priv {int (* get_port_link ) (int) ;TYPE_1__* chip; } ;
struct TYPE_2__ {int (* read_port_status ) (struct ar8xxx_priv*,int) ;int /*<<< orphan*/  (* read_port_eee_status ) (struct ar8xxx_priv*,int) ;} ;

/* Variables and functions */
#define  AR8216_PORT_SPEED_1000M 130 
#define  AR8216_PORT_SPEED_100M 129 
#define  AR8216_PORT_SPEED_10M 128 
 int AR8216_PORT_STATUS_DUPLEX ; 
 int AR8216_PORT_STATUS_LINK_AUTO ; 
 int AR8216_PORT_STATUS_LINK_UP ; 
 int AR8216_PORT_STATUS_RXFLOW ; 
 int AR8216_PORT_STATUS_SPEED ; 
 int AR8216_PORT_STATUS_SPEED_S ; 
 int AR8216_PORT_STATUS_TXFLOW ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_10 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_100 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_1000 ; 
 int /*<<< orphan*/  SWITCH_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  memset (struct switch_port_link*,char,int) ; 
 int stub1 (struct ar8xxx_priv*,int) ; 
 int stub2 (int) ; 
 int /*<<< orphan*/  stub3 (struct ar8xxx_priv*,int) ; 

__attribute__((used)) static void
ar8216_read_port_link(struct ar8xxx_priv *priv, int port,
		      struct switch_port_link *link)
{
	u32 status;
	u32 speed;

	memset(link, '\0', sizeof(*link));

	status = priv->chip->read_port_status(priv, port);

	link->aneg = !!(status & AR8216_PORT_STATUS_LINK_AUTO);
	if (link->aneg) {
		link->link = !!(status & AR8216_PORT_STATUS_LINK_UP);
	} else {
		link->link = true;

		if (priv->get_port_link) {
			int err;

			err = priv->get_port_link(port);
			if (err >= 0)
				link->link = !!err;
		}
	}

	if (!link->link)
		return;

	link->duplex = !!(status & AR8216_PORT_STATUS_DUPLEX);
	link->tx_flow = !!(status & AR8216_PORT_STATUS_TXFLOW);
	link->rx_flow = !!(status & AR8216_PORT_STATUS_RXFLOW);

	if (link->aneg && link->duplex && priv->chip->read_port_eee_status)
		link->eee = priv->chip->read_port_eee_status(priv, port);

	speed = (status & AR8216_PORT_STATUS_SPEED) >>
		 AR8216_PORT_STATUS_SPEED_S;

	switch (speed) {
	case AR8216_PORT_SPEED_10M:
		link->speed = SWITCH_PORT_SPEED_10;
		break;
	case AR8216_PORT_SPEED_100M:
		link->speed = SWITCH_PORT_SPEED_100;
		break;
	case AR8216_PORT_SPEED_1000M:
		link->speed = SWITCH_PORT_SPEED_1000;
		break;
	default:
		link->speed = SWITCH_PORT_SPEED_UNKNOWN;
		break;
	}
}