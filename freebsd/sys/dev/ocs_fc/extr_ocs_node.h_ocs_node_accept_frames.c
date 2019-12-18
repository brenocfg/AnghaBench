#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hold_frames; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*) ; 

__attribute__((used)) static inline void
ocs_node_accept_frames(ocs_node_t *node)
{
	ocs_assert(node);
	node->hold_frames = FALSE;
}