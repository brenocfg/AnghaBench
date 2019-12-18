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
struct TYPE_3__ {int /*<<< orphan*/  references; int /*<<< orphan*/  path_order; } ;
typedef  TYPE_1__ pack_context_t ;

/* Variables and functions */
 scalar_t__ compare_path_order ; 
 scalar_t__ compare_references ; 
 int /*<<< orphan*/  svn_sort__array (int /*<<< orphan*/ ,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void
sort_reps(pack_context_t *context)
{
  svn_sort__array(context->path_order,
                  (int (*)(const void *, const void *))compare_path_order);
  svn_sort__array(context->references,
                  (int (*)(const void *, const void *))compare_references);
}