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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u64 knl_sad_limit(u32 reg)
{
	return (GET_BITFIELD(reg, 7, 26) << 26) | 0x3ffffff;
}