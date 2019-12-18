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
typedef  int u8 ;
typedef  enum CUDBG_DBG_ENTITY_TYPE { ____Placeholder_CUDBG_DBG_ENTITY_TYPE } CUDBG_DBG_ENTITY_TYPE ;

/* Variables and functions */

__attribute__((used)) static inline void reset_dbg_bitmap(u8 *bitmap, enum CUDBG_DBG_ENTITY_TYPE type)
{
	int index = type / 8;
	int bit = type % 8;

	bitmap[index] &= ~(1 << bit);
}