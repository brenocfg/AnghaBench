#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_4__ {scalar_t__ sequence_number; } ;
struct TYPE_5__ {TYPE_1__ access; } ;
typedef  TYPE_2__ limited_rights_t ;

/* Variables and functions */
 scalar_t__ NO_SEQUENCE_NUMBER ; 

__attribute__((used)) static svn_boolean_t
has_local_rule(const limited_rights_t *rights)
{
  return rights->access.sequence_number != NO_SEQUENCE_NUMBER;
}