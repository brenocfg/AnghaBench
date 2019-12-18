#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_1__ ;

/* Type definitions */
struct TYPE_45__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_46__ {TYPE_7__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_47__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_48__ {scalar_t__ kind; } ;
typedef  TYPE_4__ svn_checksum_t ;
struct TYPE_49__ {char* edit_key; char* data_key; char const* data_key_uniquifier; } ;
typedef  TYPE_5__ node_revision_t ;
struct TYPE_50__ {scalar_t__ kind; int /*<<< orphan*/  id; TYPE_2__* fs; } ;
typedef  TYPE_6__ dag_node_t ;
struct TYPE_51__ {scalar_t__ format; } ;
typedef  TYPE_7__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 scalar_t__ SVN_ERR_FS_NO_SUCH_CHECKSUM_REP ; 
 scalar_t__ SVN_FS_BASE__MIN_REP_SHARING_FORMAT ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_4__ const*,TYPE_4__*) ; 
 scalar_t__ svn_checksum_md5 ; 
 TYPE_3__* svn_checksum_mismatch_err (TYPE_4__ const*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (TYPE_6__*,char const*) ; 
 TYPE_3__* svn_fs_base__delete_rep_if_mutable (TYPE_2__*,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_fs_base__rep_contents_checksums (TYPE_4__**,TYPE_4__**,TYPE_2__*,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_fs_bdb__get_checksum_rep (char const**,TYPE_2__*,TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_fs_bdb__get_node_revision (TYPE_5__**,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_fs_bdb__put_node_revision (TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_fs_bdb__reserve_rep_reuse_id (char const**,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_base__dag_finalize_edits(dag_node_t *file,
                                const svn_checksum_t *checksum,
                                const char *txn_id,
                                trail_t *trail,
                                apr_pool_t *pool)
{
  svn_fs_t *fs = file->fs;   /* just for nicer indentation */
  node_revision_t *noderev;
  const char *old_data_key, *new_data_key, *useless_data_key = NULL;
  const char *data_key_uniquifier = NULL;
  svn_checksum_t *md5_checksum, *sha1_checksum;
  base_fs_data_t *bfd = fs->fsap_data;

  /* Make sure our node is a file. */
  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       _("Attempted to set textual contents of a *non*-file node"));

  /* Make sure our node is mutable. */
  if (! svn_fs_base__dag_check_mutable(file, txn_id))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to set textual contents of an immutable node"));

  /* Get the node revision. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, file->id,
                                        trail, pool));

  /* If this node has no EDIT-DATA-KEY, this is a no-op. */
  if (! noderev->edit_key)
    return SVN_NO_ERROR;

  /* Get our representation's checksums. */
  SVN_ERR(svn_fs_base__rep_contents_checksums(&md5_checksum, &sha1_checksum,
                                              fs, noderev->edit_key,
                                              trail, pool));

  /* If our caller provided a checksum of the right kind to compare, do so. */
  if (checksum)
    {
      svn_checksum_t *test_checksum;

      if (checksum->kind == svn_checksum_md5)
        test_checksum = md5_checksum;
      else if (checksum->kind == svn_checksum_sha1)
        test_checksum = sha1_checksum;
      else
        return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL, NULL);

      if (! svn_checksum_match(checksum, test_checksum))
        return svn_checksum_mismatch_err(checksum, test_checksum, pool,
                        _("Checksum mismatch on representation '%s'"),
                        noderev->edit_key);
    }

  /* Now, we want to delete the old representation and replace it with
     the new.  Of course, we don't actually delete anything until
     everything is being properly referred to by the node-revision
     skel.

     Now, if the result of all this editing is that we've created a
     representation that describes content already represented
     immutably in our database, we don't even need to keep these edits.
     We can simply point our data_key at that pre-existing
     representation and throw away our work!  In this situation,
     though, we'll need a unique ID to help other code distinguish
     between "the contents weren't touched" and "the contents were
     touched but still look the same" (to state it oversimply).  */
  old_data_key = noderev->data_key;
  if (sha1_checksum && bfd->format >= SVN_FS_BASE__MIN_REP_SHARING_FORMAT)
    {
      svn_error_t *err = svn_fs_bdb__get_checksum_rep(&new_data_key, fs,
                                                      sha1_checksum,
                                                      trail, pool);
      if (! err)
        {
          useless_data_key = noderev->edit_key;
          err = svn_fs_bdb__reserve_rep_reuse_id(&data_key_uniquifier,
                                                 trail->fs, trail, pool);
        }
      else if (err && (err->apr_err == SVN_ERR_FS_NO_SUCH_CHECKSUM_REP))
        {
          svn_error_clear(err);
          err = SVN_NO_ERROR;
          new_data_key = noderev->edit_key;
        }
      SVN_ERR(err);
    }
  else
    {
      new_data_key = noderev->edit_key;
    }

  noderev->data_key = new_data_key;
  noderev->data_key_uniquifier = data_key_uniquifier;
  noderev->edit_key = NULL;

  SVN_ERR(svn_fs_bdb__put_node_revision(fs, file->id, noderev, trail, pool));

  /* Only *now* can we safely destroy the old representation (if it
     even existed in the first place). */
  if (old_data_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, old_data_key, txn_id,
                                               trail, pool));

  /* If we've got a discardable rep (probably because we ended up
     re-using a preexisting one), throw out the discardable rep. */
  if (useless_data_key)
    SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, useless_data_key,
                                               txn_id, trail, pool));

  return SVN_NO_ERROR;
}