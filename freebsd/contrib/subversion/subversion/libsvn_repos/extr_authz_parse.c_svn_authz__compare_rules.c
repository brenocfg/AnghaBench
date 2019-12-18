#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ repos; } ;
typedef  TYPE_1__ authz_rule_t ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 
 int svn_authz__compare_paths (TYPE_1__ const*,TYPE_1__ const*) ; 

int
svn_authz__compare_rules(const authz_rule_t *a, const authz_rule_t *b)
{
  int diff = svn_authz__compare_paths(a, b);
  if (diff)
    return diff;

  /* Repository names are interned, too. */
  if (a->repos != b->repos)
    return strcmp(a->repos, b->repos);

  return 0;
}