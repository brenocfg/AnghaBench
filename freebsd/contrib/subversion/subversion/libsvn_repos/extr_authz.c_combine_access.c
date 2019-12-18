#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sequence_number; } ;
struct TYPE_6__ {TYPE_1__ access; } ;
typedef  TYPE_2__ limited_rights_t ;

/* Variables and functions */

__attribute__((used)) static void
combine_access(limited_rights_t *target,
               const limited_rights_t *rights)
{
  /* This implies the check for NO_SEQUENCE_NUMBER, i.e no rights being
   * specified. */
  if (target->access.sequence_number < rights->access.sequence_number)
    target->access = rights->access;
}