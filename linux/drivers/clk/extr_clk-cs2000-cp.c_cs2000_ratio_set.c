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
struct cs2000_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ CH_SIZE_ERR (int) ; 
 int EINVAL ; 
 unsigned int RATIO_REG_SIZE ; 
 int /*<<< orphan*/  Ratio_Add (int,unsigned int) ; 
 int /*<<< orphan*/  Ratio_Val (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cs2000_rate_to_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cs2000_write (struct cs2000_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs2000_ratio_set(struct cs2000_priv *priv,
			    int ch, u32 rate_in, u32 rate_out)
{
	u32 val;
	unsigned int i;
	int ret;

	if (CH_SIZE_ERR(ch))
		return -EINVAL;

	val = cs2000_rate_to_ratio(rate_in, rate_out);
	for (i = 0; i < RATIO_REG_SIZE; i++) {
		ret = cs2000_write(priv,
				   Ratio_Add(ch, i),
				   Ratio_Val(val, i));
		if (ret < 0)
			return ret;
	}

	return 0;
}