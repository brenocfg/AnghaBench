#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  dump_props; int /*<<< orphan*/  pool; int /*<<< orphan*/  deleted_props; int /*<<< orphan*/  props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 char* svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
change_file_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;

  if (svn_property_kind2(name) != svn_prop_regular_kind)
    return SVN_NO_ERROR;

  if (value)
    svn_hash_sets(fb->props,
                  apr_pstrdup(fb->pool, name),
                  svn_string_dup(value, fb->pool));
  else
    svn_hash_sets(fb->deleted_props, apr_pstrdup(fb->pool, name), "");

  /* Dump the property headers and wait; close_file might need
     to write text headers too depending on whether
     apply_textdelta is called */
  fb->dump_props = TRUE;

  return SVN_NO_ERROR;
}