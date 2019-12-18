#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int (* bar1_idx_read ) (struct octeon_device*,int) ;int /*<<< orphan*/  (* bar1_idx_write ) (struct octeon_device*,int,int) ;} ;
struct octeon_device {TYPE_1__ fn_list; } ;

/* Variables and functions */
 int stub1 (struct octeon_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct octeon_device*,int,int) ; 

__attribute__((used)) static inline void
lio_toggle_bar1_swapmode(struct octeon_device *oct, uint32_t idx)
{
	uint32_t mask;

	mask = oct->fn_list.bar1_idx_read(oct, idx);
	mask = (mask & 0x2) ? (mask & ~2) : (mask | 2);
	oct->fn_list.bar1_idx_write(oct, idx, mask);
}