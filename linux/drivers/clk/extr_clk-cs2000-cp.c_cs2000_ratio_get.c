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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 unsigned int RATIO_REG_SIZE ; 
 int /*<<< orphan*/  Ratio_Add (int,unsigned int) ; 
 int /*<<< orphan*/  Val_Ratio (scalar_t__,unsigned int) ; 
 scalar_t__ cs2000_read (struct cs2000_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cs2000_ratio_get(struct cs2000_priv *priv, int ch)
{
	s32 tmp;
	u32 val;
	unsigned int i;

	val = 0;
	for (i = 0; i < RATIO_REG_SIZE; i++) {
		tmp = cs2000_read(priv, Ratio_Add(ch, i));
		if (tmp < 0)
			return 0;

		val |= Val_Ratio(tmp, i);
	}

	return val;
}