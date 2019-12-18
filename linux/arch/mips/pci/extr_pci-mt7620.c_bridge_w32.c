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

/* Variables and functions */
 unsigned int bridge_base ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void bridge_w32(u32 val, unsigned reg)
{
	iowrite32(val, bridge_base + reg);
}