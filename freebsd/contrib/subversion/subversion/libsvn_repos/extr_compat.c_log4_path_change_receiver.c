#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ path; scalar_t__ prop_mod; scalar_t__ text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  change_kind; } ;
typedef  TYPE_2__ svn_repos_path_change_t ;
struct TYPE_10__ {void* props_modified; void* text_modified; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  action; } ;
typedef  TYPE_3__ svn_log_changed_path2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/ * changes; int /*<<< orphan*/  changes_pool; } ;
typedef  TYPE_4__ log_entry_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_change_kind_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_log_changed_path2_create (int /*<<< orphan*/ ) ; 
 void* svn_tristate_false ; 
 void* svn_tristate_true ; 

__attribute__((used)) static svn_error_t *
log4_path_change_receiver(void *baton,
                          svn_repos_path_change_t *change,
                          apr_pool_t *scratch_pool)
{
  log_entry_receiver_baton_t *b = baton;
  svn_log_changed_path2_t *change_copy;
  const char *path = apr_pstrmemdup(b->changes_pool, change->path.data,
                                    change->path.len);

  /* Create a deep copy of the temporary CHANGE struct. */
  change_copy = svn_log_changed_path2_create(b->changes_pool);
  change_copy->action = path_change_kind_to_char(change->change_kind);

  if (change->copyfrom_path)
    change_copy->copyfrom_path = apr_pstrdup(b->changes_pool,
                                             change->copyfrom_path);

  change_copy->copyfrom_rev = change->copyfrom_rev;
  change_copy->node_kind = change->node_kind;
  change_copy->text_modified = change->text_mod ? svn_tristate_true
                                                : svn_tristate_false;
  change_copy->props_modified = change->prop_mod ? svn_tristate_true
                                                 : svn_tristate_false;

  /* Auto-create the CHANGES container (happens for each first change
   * in any revison. */
  if (b->changes == NULL)
    b->changes = svn_hash__make(b->changes_pool);

  /* Add change to per-revision collection. */
  apr_hash_set(b->changes, path, change->path.len, change_copy);

  return SVN_NO_ERROR;
}