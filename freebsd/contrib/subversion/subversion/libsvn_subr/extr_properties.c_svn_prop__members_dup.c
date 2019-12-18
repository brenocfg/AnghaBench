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
struct TYPE_3__ {scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ svn_string_dup (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svn_prop__members_dup(svn_prop_t *prop, apr_pool_t *pool)
{
  if (prop->name)
    prop->name = apr_pstrdup(pool, prop->name);
  if (prop->value)
    prop->value = svn_string_dup(prop->value, pool);
}