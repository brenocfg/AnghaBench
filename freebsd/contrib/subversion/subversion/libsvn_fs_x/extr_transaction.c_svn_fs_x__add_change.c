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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_4__ {char const* data; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  mergeinfo_mod; void* prop_mod; void* text_mod; int /*<<< orphan*/  change_kind; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_APPEND ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_changes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_tristate_false ; 
 int /*<<< orphan*/  svn_tristate_true ; 

svn_error_t *
svn_fs_x__add_change(svn_fs_t *fs,
                     svn_fs_x__txn_id_t txn_id,
                     const char *path,
                     svn_fs_path_change_kind_t change_kind,
                     svn_boolean_t text_mod,
                     svn_boolean_t prop_mod,
                     svn_boolean_t mergeinfo_mod,
                     svn_node_kind_t node_kind,
                     svn_revnum_t copyfrom_rev,
                     const char *copyfrom_path,
                     apr_pool_t *scratch_pool)
{
  apr_file_t *file;
  svn_fs_x__change_t change;
  apr_hash_t *changes = apr_hash_make(scratch_pool);

  /* Not using APR_BUFFERED to append change in one atomic write operation. */
  SVN_ERR(svn_io_file_open(&file,
                           svn_fs_x__path_txn_changes(fs, txn_id,
                                                      scratch_pool),
                           APR_APPEND | APR_WRITE | APR_CREATE,
                           APR_OS_DEFAULT, scratch_pool));

  change.path.data = path;
  change.path.len = strlen(path);
  change.change_kind = change_kind;
  change.text_mod = text_mod;
  change.prop_mod = prop_mod;
  change.mergeinfo_mod = mergeinfo_mod ? svn_tristate_true
                                       : svn_tristate_false;
  change.node_kind = node_kind;
  change.copyfrom_known = TRUE;
  change.copyfrom_rev = copyfrom_rev;
  if (copyfrom_path)
    change.copyfrom_path = apr_pstrdup(scratch_pool, copyfrom_path);

  svn_hash_sets(changes, path, &change);
  SVN_ERR(svn_fs_x__write_changes(svn_stream_from_aprfile2(file, TRUE,
                                                           scratch_pool),
                                  fs, changes, FALSE, scratch_pool));

  return svn_io_file_close(file, scratch_pool);
}