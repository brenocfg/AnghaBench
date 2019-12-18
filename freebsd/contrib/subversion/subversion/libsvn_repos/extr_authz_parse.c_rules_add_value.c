#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {scalar_t__ in_aliases; scalar_t__ in_groups; } ;
typedef  TYPE_1__ ctor_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/ * add_access_entry (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * add_alias_definition (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * groups_add_value (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rules_add_value(void *baton, svn_stringbuf_t *section,
                svn_stringbuf_t *option, svn_stringbuf_t *value)
{
  ctor_baton_t *const cb = baton;

  if (cb->in_groups)
    return groups_add_value(baton, section, option, value);

  if (cb->in_aliases)
    return add_alias_definition(cb, option, value);

  return add_access_entry(cb, section, option, value);
}