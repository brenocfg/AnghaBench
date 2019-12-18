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
struct talitos_private {scalar_t__ reg_rngu; } ;
struct hwrng {scalar_t__ priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TALITOS_EUSR_LO ; 
 int TALITOS_RNGUSR_LO_OFL ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int talitos_rng_data_present(struct hwrng *rng, int wait)
{
	struct device *dev = (struct device *)rng->priv;
	struct talitos_private *priv = dev_get_drvdata(dev);
	u32 ofl;
	int i;

	for (i = 0; i < 20; i++) {
		ofl = in_be32(priv->reg_rngu + TALITOS_EUSR_LO) &
		      TALITOS_RNGUSR_LO_OFL;
		if (ofl || !wait)
			break;
		udelay(10);
	}

	return !!ofl;
}