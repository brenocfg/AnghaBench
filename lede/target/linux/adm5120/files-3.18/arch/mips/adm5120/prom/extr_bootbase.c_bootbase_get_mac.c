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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 TYPE_1__* board_info ; 

__attribute__((used)) static inline void bootbase_get_mac(u8 *mac)
{
	int	i;

	for (i = 0; i < 6; i++)
		mac[i] = board_info->mac[i];
}