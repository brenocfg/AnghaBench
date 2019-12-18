#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min_access; int max_access; } ;
typedef  TYPE_1__ authz_rights_t ;

/* Variables and functions */

__attribute__((used)) static void
combine_rights(authz_rights_t *rights_p,
               const authz_rights_t *lhs,
               const authz_rights_t *rhs)
{
  rights_p->min_access = lhs->min_access & rhs->min_access;
  rights_p->max_access = lhs->max_access | rhs->max_access;
}