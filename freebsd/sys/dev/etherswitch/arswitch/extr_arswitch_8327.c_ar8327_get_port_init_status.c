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
typedef  int uint32_t ;
struct ar8327_port_cfg {int speed; scalar_t__ txpause; scalar_t__ rxpause; scalar_t__ duplex; int /*<<< orphan*/  force_link; } ;

/* Variables and functions */
#define  AR8327_PORT_SPEED_10 130 
#define  AR8327_PORT_SPEED_100 129 
#define  AR8327_PORT_SPEED_1000 128 
 int AR8X16_PORT_STS_DUPLEX ; 
 int AR8X16_PORT_STS_LINK_AUTO ; 
 int AR8X16_PORT_STS_RXFLOW ; 
 int AR8X16_PORT_STS_RXMAC ; 
 int AR8X16_PORT_STS_SPEED_10 ; 
 int AR8X16_PORT_STS_SPEED_100 ; 
 int AR8X16_PORT_STS_SPEED_1000 ; 
 int AR8X16_PORT_STS_TXFLOW ; 
 int AR8X16_PORT_STS_TXMAC ; 

__attribute__((used)) static uint32_t
ar8327_get_port_init_status(struct ar8327_port_cfg *cfg)
{
	uint32_t t;

	if (!cfg->force_link)
		return (AR8X16_PORT_STS_LINK_AUTO);

	t = AR8X16_PORT_STS_TXMAC | AR8X16_PORT_STS_RXMAC;
	t |= cfg->duplex ? AR8X16_PORT_STS_DUPLEX : 0;
	t |= cfg->rxpause ? AR8X16_PORT_STS_RXFLOW : 0;
	t |= cfg->txpause ? AR8X16_PORT_STS_TXFLOW : 0;

	switch (cfg->speed) {
	case AR8327_PORT_SPEED_10:
		t |= AR8X16_PORT_STS_SPEED_10;
		break;
	case AR8327_PORT_SPEED_100:
		t |= AR8X16_PORT_STS_SPEED_100;
		break;
	case AR8327_PORT_SPEED_1000:
		t |= AR8X16_PORT_STS_SPEED_1000;
		break;
	}

	return (t);
}