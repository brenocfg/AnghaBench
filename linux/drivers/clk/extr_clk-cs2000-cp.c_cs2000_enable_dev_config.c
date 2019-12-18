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
struct cs2000_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSKIPEN ; 
 int /*<<< orphan*/  DEVICE_CFG1 ; 
 int /*<<< orphan*/  ENDEV1 ; 
 int /*<<< orphan*/  ENDEV2 ; 
 int /*<<< orphan*/  FUNC_CFG1 ; 
 int /*<<< orphan*/  FUNC_CFG2 ; 
 int /*<<< orphan*/  GLOBAL_CFG ; 
 int /*<<< orphan*/  LFRATIO_12_20 ; 
 int /*<<< orphan*/  LFRATIO_MASK ; 
 int cs2000_bset (struct cs2000_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs2000_enable_dev_config(struct cs2000_priv *priv, bool enable)
{
	int ret;

	ret = cs2000_bset(priv, DEVICE_CFG1, ENDEV1,
			  enable ? ENDEV1 : 0);
	if (ret < 0)
		return ret;

	ret = cs2000_bset(priv, GLOBAL_CFG,  ENDEV2,
			  enable ? ENDEV2 : 0);
	if (ret < 0)
		return ret;

	ret = cs2000_bset(priv, FUNC_CFG1, CLKSKIPEN,
			  enable ? CLKSKIPEN : 0);
	if (ret < 0)
		return ret;

	/* FIXME: for Static ratio mode */
	ret = cs2000_bset(priv, FUNC_CFG2, LFRATIO_MASK,
			  LFRATIO_12_20);
	if (ret < 0)
		return ret;

	return 0;
}