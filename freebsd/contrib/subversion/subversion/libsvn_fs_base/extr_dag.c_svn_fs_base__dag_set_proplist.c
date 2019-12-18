#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_39__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_40__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_41__ {TYPE_7__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
struct TYPE_42__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct TYPE_43__ {char* prop_key; } ;
typedef  TYPE_5__ node_revision_t ;
struct TYPE_44__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_6__ dag_node_t ;
struct TYPE_45__ {scalar_t__ format; } ;
typedef  TYPE_7__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 scalar_t__ SVN_ERR_FS_NO_SUCH_CHECKSUM_REP ; 
 scalar_t__ SVN_FS_BASE__MIN_REP_SHARING_FORMAT ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__* svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (TYPE_6__*,char const*) ; 
 TYPE_3__* svn_fs_base__dag_get_fs (TYPE_6__*) ; 
 TYPE_4__* svn_fs_base__delete_rep_if_mutable (TYPE_3__*,char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_fs_base__get_mutable_rep (char const**,char const*,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_base__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_fs_base__rep_contents_write_stream (int /*<<< orphan*/ **,TYPE_3__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__same_keys (char const*,char const*) ; 
 TYPE_4__* svn_fs_bdb__get_checksum_rep (char const**,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_fs_bdb__get_node_revision (TYPE_5__**,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_fs_bdb__put_node_revision (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_skel__unparse_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_stream_close (int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_set_proplist(dag_node_t *node,
                              const apr_hash_t *proplist,
                              const char *txn_id,
                              trail_t *trail,
                              apr_pool_t *pool)
{
  node_revision_t *noderev;
  const char *rep_key, *mutable_rep_key;
  svn_fs_t *fs = svn_fs_base__dag_get_fs(node);
  svn_stream_t *wstream;
  apr_size_t len;
  svn_skel_t *proplist_skel;
  svn_stringbuf_t *raw_proplist_buf;
  base_fs_data_t *bfd = fs->fsap_data;

  /* Sanity check: this node better be mutable! */
  if (! svn_fs_base__dag_check_mutable(node, txn_id))
    {
      svn_string_t *idstr = svn_fs_base__id_unparse(node->id, pool);
      return svn_error_createf
        (SVN_ERR_FS_NOT_MUTABLE, NULL,
         _("Can't set proplist on *immutable* node-revision %s"),
         idstr->data);
    }

  /* Go get a fresh NODE-REVISION for this node. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, node->id,
                                        trail, pool));
  rep_key = noderev->prop_key;

  /* Flatten the proplist into a string. */
  SVN_ERR(svn_skel__unparse_proplist(&proplist_skel, proplist, pool));
  raw_proplist_buf = svn_skel__unparse(proplist_skel, pool);

  /* If this repository supports representation sharing, and the
     resulting property list is exactly the same as another string in
     the database, just use the previously existing string and get
     outta here. */
  if (bfd->format >= SVN_FS_BASE__MIN_REP_SHARING_FORMAT)
    {
      svn_error_t *err;
      const char *dup_rep_key;
      svn_checksum_t *checksum;

      SVN_ERR(svn_checksum(&checksum, svn_checksum_sha1, raw_proplist_buf->data,
                           raw_proplist_buf->len, pool));

      err = svn_fs_bdb__get_checksum_rep(&dup_rep_key, fs, checksum,
                                         trail, pool);
      if (! err)
        {
          if (noderev->prop_key)
            SVN_ERR(svn_fs_base__delete_rep_if_mutable(fs, noderev->prop_key,
                                                       txn_id, trail, pool));
          noderev->prop_key = dup_rep_key;
          return svn_fs_bdb__put_node_revision(fs, node->id, noderev,
                                               trail, pool);
        }
      else if (err)
        {
          if (err->apr_err != SVN_ERR_FS_NO_SUCH_CHECKSUM_REP)
            return svn_error_trace(err);

          svn_error_clear(err);
          err = SVN_NO_ERROR;
        }
    }

  /* Get a mutable version of this rep (updating the node revision if
     this isn't a NOOP)  */
  SVN_ERR(svn_fs_base__get_mutable_rep(&mutable_rep_key, rep_key,
                                       fs, txn_id, trail, pool));
  if (! svn_fs_base__same_keys(mutable_rep_key, rep_key))
    {
      noderev->prop_key = mutable_rep_key;
      SVN_ERR(svn_fs_bdb__put_node_revision(fs, node->id, noderev,
                                            trail, pool));
    }

  /* Replace the old property list with the new one. */
  SVN_ERR(svn_fs_base__rep_contents_write_stream(&wstream, fs,
                                                 mutable_rep_key, txn_id,
                                                 TRUE, trail, pool));
  len = raw_proplist_buf->len;
  SVN_ERR(svn_stream_write(wstream, raw_proplist_buf->data, &len));
  SVN_ERR(svn_stream_close(wstream));

  return SVN_NO_ERROR;
}