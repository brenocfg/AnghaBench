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
typedef  int /*<<< orphan*/  u32 ;
struct mcs814x_rng_priv {scalar_t__ regs; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 scalar_t__ RND ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int mcs814x_rng_data_read(struct hwrng *rng, u32 *buffer)
{
	struct mcs814x_rng_priv *priv = (struct mcs814x_rng_priv *)rng->priv;

	*buffer = readl_relaxed(priv->regs + RND);

	return 4;
}