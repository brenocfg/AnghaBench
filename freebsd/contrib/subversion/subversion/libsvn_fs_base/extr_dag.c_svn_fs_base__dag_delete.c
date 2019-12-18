#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {char* data_key; } ;
typedef  TYPE_3__ node_revision_t ;
struct TYPE_16__ {scalar_t__ kind; int /*<<< orphan*/ * fs; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_ENTRY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_delete_if_mutable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_fs (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__get_mutable_rep (char const**,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__parse_entries_skel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rep_contents (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rep_contents_write_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__same_keys (char const*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__unparse_entries_skel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 
 int /*<<< orphan*/ * svn_skel__parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_delete(dag_node_t *parent,
                        const char *name,
                        const char *txn_id,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  node_revision_t *parent_noderev;
  const char *rep_key, *mutable_rep_key;
  apr_hash_t *entries = NULL;
  svn_skel_t *entries_skel;
  svn_fs_t *fs = parent->fs;
  svn_string_t str;
  svn_fs_id_t *id = NULL;
  dag_node_t *node;

  /* Make sure parent is a directory. */
  if (parent->kind != svn_node_dir)
    return svn_error_createf
      (SVN_ERR_FS_NOT_DIRECTORY, NULL,
       _("Attempted to delete entry '%s' from *non*-directory node"), name);

  /* Make sure parent is mutable. */
  if (! svn_fs_base__dag_check_mutable(parent, txn_id))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to delete entry '%s' from immutable directory node"),
       name);

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       _("Attempted to delete a node with an illegal name '%s'"), name);

  /* Get a fresh NODE-REVISION for the parent node. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&parent_noderev, fs, parent->id,
                                        trail, pool));

  /* Get the key for the parent's entries list (data) representation. */
  rep_key = parent_noderev->data_key;

  /* No REP_KEY means no representation, and no representation means
     no data, and no data means no entries...there's nothing here to
     delete! */
  if (! rep_key)
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_ENTRY, NULL,
       _("Delete failed: directory has no entry '%s'"), name);

  /* Ensure we have a key to a mutable representation of the entries
     list.  We'll have to update the NODE-REVISION if it points to an
     immutable version.  */
  SVN_ERR(svn_fs_base__get_mutable_rep(&mutable_rep_key, rep_key,
                                       fs, txn_id, trail, pool));
  if (! svn_fs_base__same_keys(mutable_rep_key, rep_key))
    {
      parent_noderev->data_key = mutable_rep_key;
      SVN_ERR(svn_fs_bdb__put_node_revision(fs, parent->id, parent_noderev,
                                            trail, pool));
    }

  /* Read the representation, then use it to get the string that holds
     the entries list.  Parse that list into a skel, and parse *that*
     into a hash. */

  SVN_ERR(svn_fs_base__rep_contents(&str, fs, rep_key, trail, pool));
  entries_skel = svn_skel__parse(str.data, str.len, pool);
  if (entries_skel)
    SVN_ERR(svn_fs_base__parse_entries_skel(&entries, entries_skel, pool));

  /* Find NAME in the ENTRIES skel.  */
  if (entries)
    id = svn_hash_gets(entries, name);

  /* If we never found ID in ENTRIES (perhaps because there are no
     ENTRIES, perhaps because ID just isn't in the existing ENTRIES
     ... it doesn't matter), return an error.  */
  if (! id)
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_ENTRY, NULL,
       _("Delete failed: directory has no entry '%s'"), name);

  /* Use the ID of this ENTRY to get the entry's node.  */
  SVN_ERR(svn_fs_base__dag_get_node(&node, svn_fs_base__dag_get_fs(parent),
                                    id, trail, pool));

  /* If mutable, remove it and any mutable children from db. */
  SVN_ERR(svn_fs_base__dag_delete_if_mutable(parent->fs, id, txn_id,
                                             trail, pool));

  /* Remove this entry from its parent's entries list. */
  svn_hash_sets(entries, name, NULL);

  /* Replace the old entries list with the new one. */
  {
    svn_stream_t *ws;
    svn_stringbuf_t *unparsed_entries;
    apr_size_t len;

    SVN_ERR(svn_fs_base__unparse_entries_skel(&entries_skel, entries, pool));
    unparsed_entries = svn_skel__unparse(entries_skel, pool);
    SVN_ERR(svn_fs_base__rep_contents_write_stream(&ws, fs, mutable_rep_key,
                                                   txn_id, TRUE, trail,
                                                   pool));
    len = unparsed_entries->len;
    SVN_ERR(svn_stream_write(ws, unparsed_entries->data, &len));
    SVN_ERR(svn_stream_close(ws));
  }

  return SVN_NO_ERROR;
}