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
struct bwi_mac {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  NRSSI_11G_MASK ; 
 int /*<<< orphan*/  PHY_READ (struct bwi_mac*,int) ; 
 scalar_t__ __SHIFTOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int16_t
bwi_nrssi_11g(struct bwi_mac *mac)
{
	int16_t val;

#define NRSSI_11G_MASK		__BITS(13, 8)

	val = (int16_t)__SHIFTOUT(PHY_READ(mac, 0x47f), NRSSI_11G_MASK);
	if (val >= 32)
		val -= 64;
	return val;

#undef NRSSI_11G_MASK
}