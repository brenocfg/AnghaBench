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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  scalar_t__ svn_prop_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  propchanges; int /*<<< orphan*/  has_propchange; scalar_t__ skip; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_array_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_prop_wc_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
change_file_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;
  svn_prop_t *propchange;
  svn_prop_kind_t propkind;

  /* Skip *everything* within a newly tree-conflicted directory. */
  if (fb->skip)
    return SVN_NO_ERROR;

  propkind = svn_property_kind2(name);
  if (propkind == svn_prop_wc_kind)
    return SVN_NO_ERROR;
  else if (propkind == svn_prop_regular_kind)
    fb->has_propchange = TRUE;

  propchange = apr_array_push(fb->propchanges);
  propchange->name = apr_pstrdup(fb->pool, name);
  propchange->value = svn_string_dup(value, fb->pool);

  return SVN_NO_ERROR;
}