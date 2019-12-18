#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
struct TYPE_12__ {int /*<<< orphan*/  created_path; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (TYPE_1__ const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_file_checksum (TYPE_1__**,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_finalize_edits(dag_node_t *file,
                              const svn_checksum_t *checksum,
                              apr_pool_t *pool)
{
  if (checksum)
    {
      svn_checksum_t *file_checksum;

      SVN_ERR(svn_fs_fs__dag_file_checksum(&file_checksum, file,
                                           checksum->kind, pool));
      if (!svn_checksum_match(checksum, file_checksum))
        return svn_checksum_mismatch_err(checksum, file_checksum, pool,
                                         _("Checksum mismatch for '%s'"),
                                         file->created_path);
    }

  return SVN_NO_ERROR;
}