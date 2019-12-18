#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
struct TYPE_6__ {TYPE_3__* fs; scalar_t__ is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_mergeinfo_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_8__ {int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NOT_REVISION_ROOT ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_FS_FS__MIN_MERGEINFO_FORMAT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * get_mergeinfos_for_paths (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__fs_supports_mergeinfo (TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
fs_get_mergeinfo(svn_fs_root_t *root,
                 const apr_array_header_t *paths,
                 svn_mergeinfo_inheritance_t inherit,
                 svn_boolean_t include_descendants,
                 svn_boolean_t adjust_inherited_mergeinfo,
                 svn_fs_mergeinfo_receiver_t receiver,
                 void *baton,
                 apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = root->fs->fsap_data;

  /* We require a revision root. */
  if (root->is_txn_root)
    return svn_error_create(SVN_ERR_FS_NOT_REVISION_ROOT, NULL, NULL);

  /* We have to actually be able to find the mergeinfo metadata! */
  if (! svn_fs_fs__fs_supports_mergeinfo(root->fs))
    return svn_error_createf
      (SVN_ERR_UNSUPPORTED_FEATURE, NULL,
       _("Querying mergeinfo requires version %d of the FSFS filesystem "
         "schema; filesystem '%s' uses only version %d"),
       SVN_FS_FS__MIN_MERGEINFO_FORMAT, root->fs->path, ffd->format);

  /* Retrieve a path -> mergeinfo hash mapping. */
  return get_mergeinfos_for_paths(root, paths, inherit,
                                  include_descendants,
                                  adjust_inherited_mergeinfo,
                                  receiver, baton,
                                  scratch_pool);
}