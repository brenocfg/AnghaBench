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
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int M_ZERO ; 
 int /*<<< orphan*/  pcpu_zone_64 ; 
 int /*<<< orphan*/  uma_zalloc_pcpu (int /*<<< orphan*/ ,int) ; 

counter_u64_t
counter_u64_alloc(int flags)
{

	return (uma_zalloc_pcpu(pcpu_zone_64, flags | M_ZERO));
}