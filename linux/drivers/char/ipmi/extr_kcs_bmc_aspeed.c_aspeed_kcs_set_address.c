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
typedef  int u16 ;
struct kcs_bmc {int channel; } ;
struct aspeed_kcs_bmc {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC_HICR4 ; 
 int /*<<< orphan*/  LPC_HICR4_LADR12AS ; 
 int /*<<< orphan*/  LPC_LADR12H ; 
 int /*<<< orphan*/  LPC_LADR12L ; 
 int /*<<< orphan*/  LPC_LADR3H ; 
 int /*<<< orphan*/  LPC_LADR3L ; 
 int /*<<< orphan*/  LPC_LADR4 ; 
 struct aspeed_kcs_bmc* kcs_bmc_priv (struct kcs_bmc*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aspeed_kcs_set_address(struct kcs_bmc *kcs_bmc, u16 addr)
{
	struct aspeed_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);

	switch (kcs_bmc->channel) {
	case 1:
		regmap_update_bits(priv->map, LPC_HICR4,
				LPC_HICR4_LADR12AS, 0);
		regmap_write(priv->map, LPC_LADR12H, addr >> 8);
		regmap_write(priv->map, LPC_LADR12L, addr & 0xFF);
		break;

	case 2:
		regmap_update_bits(priv->map, LPC_HICR4,
				LPC_HICR4_LADR12AS, LPC_HICR4_LADR12AS);
		regmap_write(priv->map, LPC_LADR12H, addr >> 8);
		regmap_write(priv->map, LPC_LADR12L, addr & 0xFF);
		break;

	case 3:
		regmap_write(priv->map, LPC_LADR3H, addr >> 8);
		regmap_write(priv->map, LPC_LADR3L, addr & 0xFF);
		break;

	case 4:
		regmap_write(priv->map, LPC_LADR4, ((addr + 1) << 16) |
			addr);
		break;

	default:
		break;
	}
}