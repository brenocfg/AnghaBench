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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  board_id; } ;

/* Variables and functions */
 TYPE_1__* board_info ; 
 int /*<<< orphan*/  prom_read_be16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 bootbase_get_board_id(void)
{
	return prom_read_be16(&board_info->board_id);
}