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
typedef  TYPE_1__* vm_page_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int ref_count; } ;

/* Variables and functions */

__attribute__((used)) static __inline boolean_t
pt2pg_is_empty(vm_page_t m)
{

	return (m->ref_count == 1);
}