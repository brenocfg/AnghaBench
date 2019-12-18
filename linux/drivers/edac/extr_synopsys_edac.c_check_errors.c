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
struct synps_platform_data {int (* get_error_info ) (struct synps_edac_priv*) ;} ;
struct TYPE_2__ {scalar_t__ ue_cnt; scalar_t__ ce_cnt; } ;
struct synps_edac_priv {int /*<<< orphan*/  ue_cnt; int /*<<< orphan*/  ce_cnt; TYPE_1__ stat; struct synps_platform_data* p_data; } ;
struct mem_ctl_info {struct synps_edac_priv* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_error (struct mem_ctl_info*,TYPE_1__*) ; 
 int stub1 (struct synps_edac_priv*) ; 

__attribute__((used)) static void check_errors(struct mem_ctl_info *mci)
{
	const struct synps_platform_data *p_data;
	struct synps_edac_priv *priv;
	int status;

	priv = mci->pvt_info;
	p_data = priv->p_data;

	status = p_data->get_error_info(priv);
	if (status)
		return;

	priv->ce_cnt += priv->stat.ce_cnt;
	priv->ue_cnt += priv->stat.ue_cnt;
	handle_error(mci, &priv->stat);

	edac_dbg(3, "Total error count CE %d UE %d\n",
		 priv->ce_cnt, priv->ue_cnt);
}