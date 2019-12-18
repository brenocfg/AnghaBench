#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct TYPE_3__ {void* limit; scalar_t__ dscp; void* nh4; void* nat; void* fib; void* netgraph; void* skipto; void* divert; void* pipe; void* tag; } ;
typedef  TYPE_1__ ipfw_table_value ;

/* Variables and functions */

__attribute__((used)) static void
set_legacy_value(uint32_t val, ipfw_table_value *v)
{
	v->tag = val;
	v->pipe = val;
	v->divert = val;
	v->skipto = val;
	v->netgraph = val;
	v->fib = val;
	v->nat = val;
	v->nh4 = val;
	v->dscp = (uint8_t)val;
	v->limit = val;
}