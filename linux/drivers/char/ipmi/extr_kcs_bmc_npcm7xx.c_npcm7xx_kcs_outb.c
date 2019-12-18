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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct npcm7xx_kcs_bmc {int /*<<< orphan*/  map; } ;
struct kcs_bmc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 struct npcm7xx_kcs_bmc* kcs_bmc_priv (struct kcs_bmc*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm7xx_kcs_outb(struct kcs_bmc *kcs_bmc, u32 reg, u8 data)
{
	struct npcm7xx_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);
	int rc;

	rc = regmap_write(priv->map, reg, data);
	WARN(rc != 0, "regmap_write() failed: %d\n", rc);
}