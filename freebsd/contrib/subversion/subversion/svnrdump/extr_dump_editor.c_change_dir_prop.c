#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct dir_baton {int /*<<< orphan*/  dump_props; int /*<<< orphan*/  pool; int /*<<< orphan*/  deleted_props; int /*<<< orphan*/  props; TYPE_1__* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {struct dir_baton* pending_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dump_pending_dir (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 char* svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
change_dir_prop(void *parent_baton,
                const char *name,
                const svn_string_t *value,
                apr_pool_t *pool)
{
  struct dir_baton *db = parent_baton;
  svn_boolean_t this_pending;

  /* This directory is not pending, but something else is, so handle
     the "something else".  */
  this_pending = (db->eb->pending_db == db);
  if (! this_pending)
    SVN_ERR(dump_pending_dir(db->eb, pool));

  if (svn_property_kind2(name) != svn_prop_regular_kind)
    return SVN_NO_ERROR;

  if (value)
    svn_hash_sets(db->props,
                  apr_pstrdup(db->pool, name),
                  svn_string_dup(value, db->pool));
  else
    svn_hash_sets(db->deleted_props, apr_pstrdup(db->pool, name), "");

  /* Make sure we eventually output the props */
  db->dump_props = TRUE;

  return SVN_NO_ERROR;
}