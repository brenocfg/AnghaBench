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
typedef  scalar_t__ uint32_t ;
struct board_info {scalar_t__ hw_id; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 struct board_info* boards ; 

__attribute__((used)) static struct board_info *find_board_by_hwid(uint32_t hw_id)
{
	struct board_info *board;

	for (board = boards; board->id != NULL; board++) {
		if (hw_id == board->hw_id)
			return board;
	};

	return NULL;
}