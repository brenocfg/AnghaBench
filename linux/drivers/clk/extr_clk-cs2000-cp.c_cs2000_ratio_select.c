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
 int AUTORMOD ; 
 scalar_t__ CH_SIZE_ERR (int) ; 
 int /*<<< orphan*/  DEVICE_CFG1 ; 
 int /*<<< orphan*/  DEVICE_CFG2 ; 
 int EINVAL ; 
 int FRACNSRC_MASK ; 
 int FRACNSRC_STATIC ; 
 int LOCKCLK (int) ; 
 int LOCKCLK_MASK ; 
 int RSEL (int) ; 
 int RSEL_MASK ; 
 int cs2000_bset (struct cs2000_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int cs2000_ratio_select(struct cs2000_priv *priv, int ch)
{
	int ret;

	if (CH_SIZE_ERR(ch))
		return -EINVAL;

	/*
	 * FIXME
	 *
	 * this driver supports static ratio mode only at this point.
	 */
	ret = cs2000_bset(priv, DEVICE_CFG1, RSEL_MASK, RSEL(ch));
	if (ret < 0)
		return ret;

	ret = cs2000_bset(priv, DEVICE_CFG2,
			  (AUTORMOD | LOCKCLK_MASK | FRACNSRC_MASK),
			  (LOCKCLK(ch) | FRACNSRC_STATIC));
	if (ret < 0)
		return ret;

	return 0;
}