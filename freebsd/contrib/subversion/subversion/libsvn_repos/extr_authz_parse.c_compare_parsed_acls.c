#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sequence_number; int /*<<< orphan*/  rule; } ;
struct TYPE_4__ {TYPE_1__ acl; } ;
typedef  TYPE_2__ parsed_acl_t ;

/* Variables and functions */
 int svn_authz__compare_rules (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_parsed_acls(const void *va, const void *vb)
{
  const parsed_acl_t *const a = va;
  const parsed_acl_t *const b = vb;

  int cmp = svn_authz__compare_rules(&a->acl.rule, &b->acl.rule);
  if (cmp == 0)
    cmp = a->acl.sequence_number - b->acl.sequence_number;
  return cmp;
}