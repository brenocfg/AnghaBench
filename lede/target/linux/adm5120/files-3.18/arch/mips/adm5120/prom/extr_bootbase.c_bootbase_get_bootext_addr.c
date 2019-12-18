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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bootext_addr; } ;

/* Variables and functions */
 TYPE_1__* board_info ; 
 int /*<<< orphan*/  prom_read_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 bootbase_get_bootext_addr(void)
{
	return prom_read_be32(&board_info->bootext_addr);
}