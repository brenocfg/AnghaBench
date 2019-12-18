#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {char* data_key; } ;
typedef  TYPE_3__ node_revision_t ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_fs (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__get_mutable_rep (char const**,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__parse_entries_skel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rep_contents (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rep_contents_write_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__same_keys (char const*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__unparse_entries_skel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_skel__parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_entry(dag_node_t *parent,
          const char *name,
          const svn_fs_id_t *id,
          const char *txn_id,
          trail_t *trail,
          apr_pool_t *pool)
{
  node_revision_t *parent_noderev;
  const char *rep_key, *mutable_rep_key;
  apr_hash_t *entries = NULL;
  svn_stream_t *wstream;
  apr_size_t len;
  svn_string_t raw_entries;
  svn_stringbuf_t *raw_entries_buf;
  svn_skel_t *entries_skel;
  svn_fs_t *fs = svn_fs_base__dag_get_fs(parent);

  /* Get the parent's node-revision. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&parent_noderev, fs, parent->id,
                                        trail, pool));
  rep_key = parent_noderev->data_key;
  SVN_ERR(svn_fs_base__get_mutable_rep(&mutable_rep_key, rep_key,
                                       fs, txn_id, trail, pool));

  /* If the parent node already pointed at a mutable representation,
     we don't need to do anything.  But if it didn't, either because
     the parent didn't refer to any rep yet or because it referred to
     an immutable one, we must make the parent refer to the mutable
     rep we just created. */
  if (! svn_fs_base__same_keys(rep_key, mutable_rep_key))
    {
      parent_noderev->data_key = mutable_rep_key;
      SVN_ERR(svn_fs_bdb__put_node_revision(fs, parent->id, parent_noderev,
                                            trail, pool));
    }

  /* If the new representation inherited nothing, start a new entries
     list for it.  Else, go read its existing entries list. */
  if (rep_key)
    {
      SVN_ERR(svn_fs_base__rep_contents(&raw_entries, fs, rep_key,
                                        trail, pool));
      entries_skel = svn_skel__parse(raw_entries.data, raw_entries.len, pool);
      if (entries_skel)
        SVN_ERR(svn_fs_base__parse_entries_skel(&entries, entries_skel,
                                                pool));
    }

  /* If we still have no ENTRIES hash, make one here.  */
  if (! entries)
    entries = apr_hash_make(pool);

  /* Now, add our new entry to the entries list. */
  svn_hash_sets(entries, name, id);

  /* Finally, replace the old entries list with the new one. */
  SVN_ERR(svn_fs_base__unparse_entries_skel(&entries_skel, entries,
                                            pool));
  raw_entries_buf = svn_skel__unparse(entries_skel, pool);
  SVN_ERR(svn_fs_base__rep_contents_write_stream(&wstream, fs,
                                                 mutable_rep_key, txn_id,
                                                 TRUE, trail, pool));
  len = raw_entries_buf->len;
  SVN_ERR(svn_stream_write(wstream, raw_entries_buf->data, &len));
  return svn_stream_close(wstream);
}