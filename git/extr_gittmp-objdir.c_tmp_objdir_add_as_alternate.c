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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tmp_objdir {TYPE_1__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_alternates_memory (int /*<<< orphan*/ ) ; 

void tmp_objdir_add_as_alternate(const struct tmp_objdir *t)
{
	add_to_alternates_memory(t->path.buf);
}