#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct context {int /*<<< orphan*/  ignore_ancestry; int /*<<< orphan*/  source_root; int /*<<< orphan*/  target_root; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAYBE_DEMOTE_DEPTH (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_file_or_dir (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_get (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  delete (struct context*,void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delta_proplists (struct context*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_file_or_dir (struct context*,void*,int /*<<< orphan*/ ,char const*,char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 int svn_fs_compare_ids (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delta_dirs(struct context *c,
           void *dir_baton,
           svn_depth_t depth,
           const char *source_path,
           const char *target_path,
           const char *edit_path,
           apr_pool_t *pool)
{
  apr_hash_t *s_entries = 0, *t_entries = 0;
  apr_hash_index_t *hi;
  apr_pool_t *subpool;

  SVN_ERR_ASSERT(target_path);

  /* Compare the property lists.  */
  SVN_ERR(delta_proplists(c, source_path, target_path,
                          change_dir_prop, dir_baton, pool));

  /* Get the list of entries in each of source and target.  */
  SVN_ERR(svn_fs_dir_entries(&t_entries, c->target_root,
                             target_path, pool));
  if (source_path)
    SVN_ERR(svn_fs_dir_entries(&s_entries, c->source_root,
                               source_path, pool));

  /* Make a subpool for local allocations. */
  subpool = svn_pool_create(pool);

  /* Loop over the hash of entries in the target, searching for its
     partner in the source.  If we find the matching partner entry,
     use editor calls to replace the one in target with a new version
     if necessary, then remove that entry from the source entries
     hash.  If we can't find a related node in the source, we use
     editor calls to add the entry as a new item in the target.
     Having handled all the entries that exist in target, any entries
     still remaining the source entries hash represent entries that no
     longer exist in target.  Use editor calls to delete those entries
     from the target tree. */
  for (hi = apr_hash_first(pool, t_entries); hi; hi = apr_hash_next(hi))
    {
      const void *key = apr_hash_this_key(hi);
      apr_ssize_t klen = apr_hash_this_key_len(hi);
      const svn_fs_dirent_t *t_entry = apr_hash_this_val(hi);
      const svn_fs_dirent_t *s_entry;
      const char *t_fullpath;
      const char *e_fullpath;
      const char *s_fullpath;
      svn_node_kind_t tgt_kind;

      /* Clear out our subpool for the next iteration... */
      svn_pool_clear(subpool);

      tgt_kind = t_entry->kind;
      t_fullpath = svn_relpath_join(target_path, t_entry->name, subpool);
      e_fullpath = svn_relpath_join(edit_path, t_entry->name, subpool);

      /* Can we find something with the same name in the source
         entries hash? */
      if (s_entries && ((s_entry = apr_hash_get(s_entries, key, klen)) != 0))
        {
          svn_node_kind_t src_kind;

          s_fullpath = svn_relpath_join(source_path, t_entry->name, subpool);
          src_kind = s_entry->kind;

          if (depth == svn_depth_infinity
              || src_kind != svn_node_dir
              || (src_kind == svn_node_dir
                  && depth == svn_depth_immediates))
            {
              /* Use svn_fs_compare_ids() to compare our current
                 source and target ids.

                    0: means they are the same id, and this is a noop.
                   -1: means they are unrelated, so we have to delete the
                       old one and add the new one.
                    1: means the nodes are related through ancestry, so go
                       ahead and do the replace directly.  */
              int distance = svn_fs_compare_ids(s_entry->id, t_entry->id);
              if (distance == 0)
                {
                  /* no-op */
                }
              else if ((src_kind != tgt_kind)
                       || ((distance == -1) && (! c->ignore_ancestry)))
                {
                  SVN_ERR(delete(c, dir_baton, e_fullpath, subpool));
                  SVN_ERR(add_file_or_dir(c, dir_baton,
                                          MAYBE_DEMOTE_DEPTH(depth),
                                          t_fullpath, e_fullpath, tgt_kind,
                                          subpool));
                }
              else
                {
                  SVN_ERR(replace_file_or_dir(c, dir_baton,
                                              MAYBE_DEMOTE_DEPTH(depth),
                                              s_fullpath, t_fullpath,
                                              e_fullpath, tgt_kind,
                                              subpool));
                }
            }

          /*  Remove the entry from the source_hash. */
          svn_hash_sets(s_entries, key, NULL);
        }
      else
        {
          if (depth == svn_depth_infinity
              || tgt_kind != svn_node_dir
              || (tgt_kind == svn_node_dir
                  && depth == svn_depth_immediates))
            {
              SVN_ERR(add_file_or_dir(c, dir_baton,
                                      MAYBE_DEMOTE_DEPTH(depth),
                                      t_fullpath, e_fullpath, tgt_kind,
                                      subpool));
            }
        }
    }

  /* All that is left in the source entries hash are things that need
     to be deleted.  Delete them.  */
  if (s_entries)
    {
      for (hi = apr_hash_first(pool, s_entries); hi; hi = apr_hash_next(hi))
        {
          const svn_fs_dirent_t *s_entry = apr_hash_this_val(hi);
          const char *e_fullpath;
          svn_node_kind_t src_kind;

          /* Clear out our subpool for the next iteration... */
          svn_pool_clear(subpool);

          src_kind = s_entry->kind;
          e_fullpath = svn_relpath_join(edit_path, s_entry->name, subpool);

          /* Do we actually want to delete the dir if we're non-recursive? */
          if (depth == svn_depth_infinity
              || src_kind != svn_node_dir
              || (src_kind == svn_node_dir
                  && depth == svn_depth_immediates))
            {
              SVN_ERR(delete(c, dir_baton, e_fullpath, subpool));
            }
        }
    }

  /* Destroy local allocation subpool. */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}