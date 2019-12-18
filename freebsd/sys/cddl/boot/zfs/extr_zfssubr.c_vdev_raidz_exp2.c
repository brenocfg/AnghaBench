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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__* vdev_raidz_log2 ; 
 size_t* vdev_raidz_pow2 ; 

__attribute__((used)) static uint8_t
vdev_raidz_exp2(uint8_t a, int exp)
{
	if (a == 0)
		return (0);

	ASSERT(exp >= 0);
	ASSERT(vdev_raidz_log2[a] > 0 || a == 1);

	exp += vdev_raidz_log2[a];
	if (exp > 255)
		exp -= 255;

	return (vdev_raidz_pow2[exp]);
}