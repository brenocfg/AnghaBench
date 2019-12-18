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
typedef  TYPE_1__* heim_type_t ;
typedef  int /*<<< orphan*/  heim_tid_t ;
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;

/* Variables and functions */

heim_tid_t
_heim_type_get_tid(heim_type_t type)
{
    return type->tid;
}