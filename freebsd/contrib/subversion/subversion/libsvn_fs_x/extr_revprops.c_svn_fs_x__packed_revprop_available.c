#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_revprop_pack_filepath (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_revprop_packname (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_check_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 

svn_boolean_t
svn_fs_x__packed_revprop_available(svn_boolean_t *missing,
                                   svn_fs_t *fs,
                                   svn_revnum_t revision,
                                   apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  packed_revprops_t *revprops;
  svn_error_t *err;

  /* try to read the manifest file */
  revprops = apr_pcalloc(scratch_pool, sizeof(*revprops));
  revprops->revision = revision;
  err = get_revprop_packname(fs, revprops, scratch_pool, scratch_pool);

  /* if the manifest cannot be read, consider the pack files inaccessible
   * even if the file itself exists. */
  if (err)
    {
      svn_error_clear(err);
      return FALSE;
    }

  /* the respective pack file must exist (and be a file) */
  err = svn_io_check_path(get_revprop_pack_filepath(revprops,
                                                    &revprops->entry,
                                                    scratch_pool),
                          &kind, scratch_pool);
  if (err)
    {
      svn_error_clear(err);
      return FALSE;
    }

  *missing = kind == svn_node_none;
  return kind == svn_node_file;
}