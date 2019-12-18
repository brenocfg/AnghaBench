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
struct fe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_PSE_FQFC_CFG_256Q ; 
 int /*<<< orphan*/  FE_PSE_FQ_CFG ; 
 int /*<<< orphan*/  fe_csum_config (struct fe_priv*) ; 
 int /*<<< orphan*/  fe_fwd_config (struct fe_priv*) ; 
 int fe_set_clock_cycle (struct fe_priv*) ; 
 int /*<<< orphan*/  fe_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt3883_fwd_config(struct fe_priv *priv)
{
	int ret;

	ret = fe_set_clock_cycle(priv);
	if (ret)
		return ret;

	fe_fwd_config(priv);
	fe_w32(FE_PSE_FQFC_CFG_256Q, FE_PSE_FQ_CFG);
	fe_csum_config(priv);

	return ret;
}