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
struct doall_sorted {scalar_t__ type; int /*<<< orphan*/  n; TYPE_1__ const** names; } ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */

__attribute__((used)) static void do_all_sorted_fn(const OBJ_NAME *name, void *d_)
{
    struct doall_sorted *d = d_;

    if (name->type != d->type)
        return;

    d->names[d->n++] = name;
}