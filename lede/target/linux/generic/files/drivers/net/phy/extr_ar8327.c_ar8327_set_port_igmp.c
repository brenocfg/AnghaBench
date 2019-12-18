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
typedef  int u32 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8327_FRAME_ACK_CTRL_IGMP_JOIN ; 
 int AR8327_FRAME_ACK_CTRL_IGMP_LEAVE ; 
 int AR8327_FRAME_ACK_CTRL_IGMP_MLD ; 
 int AR8327_FRAME_ACK_CTRL_S (int) ; 
 int AR8327_FWD_CTRL1_IGMP_S ; 
 int AR8327_FWD_CTRL1_MC_FLOOD_S ; 
 int AR8327_REG_FRAME_ACK_CTRL (int) ; 
 int /*<<< orphan*/  AR8327_REG_FWD_CTRL1 ; 
 int BIT (int) ; 
 int /*<<< orphan*/  ar8xxx_reg_clear (struct ar8xxx_priv*,int,int) ; 
 int /*<<< orphan*/  ar8xxx_reg_set (struct ar8xxx_priv*,int,int) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ar8327_set_port_igmp(struct ar8xxx_priv *priv, int port, int enable)
{
	int reg_frame_ack = AR8327_REG_FRAME_ACK_CTRL(port);
	u32 val_frame_ack = (AR8327_FRAME_ACK_CTRL_IGMP_MLD |
			  AR8327_FRAME_ACK_CTRL_IGMP_JOIN |
			  AR8327_FRAME_ACK_CTRL_IGMP_LEAVE) <<
			 AR8327_FRAME_ACK_CTRL_S(port);

	if (enable) {
		ar8xxx_rmw(priv, AR8327_REG_FWD_CTRL1,
			   BIT(port) << AR8327_FWD_CTRL1_MC_FLOOD_S,
			   BIT(port) << AR8327_FWD_CTRL1_IGMP_S);
		ar8xxx_reg_set(priv, reg_frame_ack, val_frame_ack);
	} else {
		ar8xxx_rmw(priv, AR8327_REG_FWD_CTRL1,
			   BIT(port) << AR8327_FWD_CTRL1_IGMP_S,
			   BIT(port) << AR8327_FWD_CTRL1_MC_FLOOD_S);
		ar8xxx_reg_clear(priv, reg_frame_ack, val_frame_ack);
	}
}