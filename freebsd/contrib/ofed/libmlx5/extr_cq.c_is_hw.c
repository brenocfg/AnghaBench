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
typedef  int uint8_t ;

/* Variables and functions */
 int MLX5_CQE_OWNER_MASK ; 

__attribute__((used)) static int is_hw(uint8_t own, int n, int mask)
{
	return (own & MLX5_CQE_OWNER_MASK) ^ !!(n & (mask + 1));
}