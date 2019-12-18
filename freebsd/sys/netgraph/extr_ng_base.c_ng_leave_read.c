#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* node_p ;
struct TYPE_4__ {int /*<<< orphan*/  q_flags; } ;
struct TYPE_5__ {TYPE_1__ nd_input_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  READER_INCREMENT ; 
 int /*<<< orphan*/  atomic_subtract_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ng_leave_read(node_p node)
{
	atomic_subtract_rel_int(&node->nd_input_queue.q_flags, READER_INCREMENT);
}