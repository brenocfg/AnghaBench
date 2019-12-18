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

/* Variables and functions */
 int /*<<< orphan*/  SLCR_UNLOCK_MAGIC ; 
 int /*<<< orphan*/  SLCR_UNLOCK_OFFSET ; 
 int /*<<< orphan*/  zynq_slcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int zynq_slcr_unlock(void)
{
	zynq_slcr_write(SLCR_UNLOCK_MAGIC, SLCR_UNLOCK_OFFSET);

	return 0;
}