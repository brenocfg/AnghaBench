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
struct csrreg {int dummy; } ;
struct crom_ptr {size_t index; TYPE_1__* dir; } ;
struct crom_context {size_t depth; struct crom_ptr* stack; } ;
struct TYPE_2__ {struct csrreg* entry; } ;

/* Variables and functions */

struct csrreg *
crom_get(struct crom_context *cc)
{
	struct crom_ptr *ptr;

	ptr = &cc->stack[cc->depth];
	return (&ptr->dir->entry[ptr->index]);
}