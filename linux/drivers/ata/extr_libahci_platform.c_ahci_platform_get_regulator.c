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
typedef  size_t u32 ;
struct regulator {int dummy; } ;
struct device {int dummy; } ;
struct ahci_host_priv {struct regulator** target_pwrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* regulator_get (struct device*,char*) ; 

__attribute__((used)) static int ahci_platform_get_regulator(struct ahci_host_priv *hpriv, u32 port,
				struct device *dev)
{
	struct regulator *target_pwr;
	int rc = 0;

	target_pwr = regulator_get(dev, "target");

	if (!IS_ERR(target_pwr))
		hpriv->target_pwrs[port] = target_pwr;
	else
		rc = PTR_ERR(target_pwr);

	return rc;
}