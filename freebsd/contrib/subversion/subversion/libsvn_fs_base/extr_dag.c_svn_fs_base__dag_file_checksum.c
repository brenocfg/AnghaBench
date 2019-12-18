#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_checksum_kind_t ;
struct TYPE_5__ {int /*<<< orphan*/  data_key; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  fs; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ svn_checksum_md5 ; 
 scalar_t__ svn_checksum_sha1 ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__rep_contents_checksums (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_base__dag_file_checksum(svn_checksum_t **checksum,
                               svn_checksum_kind_t checksum_kind,
                               dag_node_t *file,
                               trail_t *trail,
                               apr_pool_t *pool)
{
  node_revision_t *noderev;

  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       _("Attempted to get checksum of a *non*-file node"));

  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, file->fs, file->id,
                                        trail, pool));
  if (! noderev->data_key)
    {
      *checksum = NULL;
      return SVN_NO_ERROR;
    }

  if (checksum_kind == svn_checksum_md5)
    return svn_fs_base__rep_contents_checksums(checksum, NULL, file->fs,
                                               noderev->data_key,
                                               trail, pool);
  else if (checksum_kind == svn_checksum_sha1)
    return svn_fs_base__rep_contents_checksums(NULL, checksum, file->fs,
                                               noderev->data_key,
                                               trail, pool);
  else
    return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL, NULL);
}