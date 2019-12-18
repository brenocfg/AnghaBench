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
struct fe_priv {int flags; } ;

/* Variables and functions */
 int FE_FLAG_JUMBO_FRAME ; 
 int FE_GDM1_JMB_EN ; 
 int /*<<< orphan*/  FE_GDMA1_FWD_CFG ; 
 int fe_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_w32 (int,int /*<<< orphan*/ ) ; 

void fe_fwd_config(struct fe_priv *priv)
{
	u32 fwd_cfg;

	fwd_cfg = fe_r32(FE_GDMA1_FWD_CFG);

	/* disable jumbo frame */
	if (priv->flags & FE_FLAG_JUMBO_FRAME)
		fwd_cfg &= ~FE_GDM1_JMB_EN;

	/* set unicast/multicast/broadcast frame to cpu */
	fwd_cfg &= ~0xffff;

	fe_w32(fwd_cfg, FE_GDMA1_FWD_CFG);
}