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
struct pt_buffer {int /*<<< orphan*/  cur_idx; int /*<<< orphan*/  cur; } ;
struct TYPE_2__ {int base; } ;

/* Variables and functions */
 TYPE_1__* TOPA_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TOPA_SHIFT ; 
 void* phys_to_virt (int) ; 

__attribute__((used)) static void *pt_buffer_region(struct pt_buffer *buf)
{
	return phys_to_virt(TOPA_ENTRY(buf->cur, buf->cur_idx)->base << TOPA_SHIFT);
}