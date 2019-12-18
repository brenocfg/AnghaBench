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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  BM_POOL_GetCounter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_BM_POOL_COUNTERS_CONTENT ; 

uint32_t
bman_count(t_Handle pool)
{

	return (BM_POOL_GetCounter(pool, e_BM_POOL_COUNTERS_CONTENT));
}