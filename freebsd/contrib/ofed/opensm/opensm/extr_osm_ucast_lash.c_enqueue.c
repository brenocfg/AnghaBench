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
struct TYPE_4__ {scalar_t__ q_state; } ;
typedef  TYPE_1__ switch_t ;
typedef  int /*<<< orphan*/  cl_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 scalar_t__ Q_MEMBER ; 
 scalar_t__ UNQUEUED ; 
 int /*<<< orphan*/  cl_list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) inline static void enqueue(cl_list_t * bfsq, switch_t * sw)
{
	CL_ASSERT(sw->q_state == UNQUEUED);
	sw->q_state = Q_MEMBER;
	cl_list_insert_tail(bfsq, sw);
}