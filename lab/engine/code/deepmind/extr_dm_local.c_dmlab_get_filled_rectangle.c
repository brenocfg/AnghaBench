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
 int /*<<< orphan*/  DEEPMIND_GET_FILLED_RECTANGLE ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_get_filled_rectangle(int rectangle_id, int* x, int* y, int* width,
                                int* height, float rgba[4]) {
  trap_DeepmindCallback(DEEPMIND_GET_FILLED_RECTANGLE, (intptr_t)rectangle_id,
                        (intptr_t)x, (intptr_t)y, (intptr_t)width,
                        (intptr_t)height, (intptr_t)rgba, 0, 0, 0, 0, 0, 0);
}