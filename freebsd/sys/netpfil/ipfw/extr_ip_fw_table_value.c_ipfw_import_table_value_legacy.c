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
typedef  void* uint32_t ;
struct table_value {void* limit; void* dscp; void* nh4; void* nat; void* fib; void* netgraph; void* skipto; void* divert; void* pipe; void* tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct table_value*,int /*<<< orphan*/ ,int) ; 

void
ipfw_import_table_value_legacy(uint32_t value, struct table_value *v)
{

	memset(v, 0, sizeof(*v));
	v->tag = value;
	v->pipe = value;
	v->divert = value;
	v->skipto = value;
	v->netgraph = value;
	v->fib = value;
	v->nat = value;
	v->nh4 = value; /* host format */
	v->dscp = value;
	v->limit = value;
}