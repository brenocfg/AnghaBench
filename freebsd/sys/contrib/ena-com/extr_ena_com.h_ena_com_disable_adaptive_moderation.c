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
struct ena_com_dev {int adaptive_coalescing; } ;

/* Variables and functions */

__attribute__((used)) static inline void ena_com_disable_adaptive_moderation(struct ena_com_dev *ena_dev)
{
	ena_dev->adaptive_coalescing = false;
}