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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  hold_frames; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t
ocs_node_frames_held(void *arg)
{
	ocs_node_t *node = (ocs_node_t *)arg;
	return node->hold_frames;
}