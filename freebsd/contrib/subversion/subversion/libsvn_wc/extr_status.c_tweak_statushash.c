#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ repos_node_status; int repos_text_status; int repos_prop_status; void* ood_changed_author; int /*<<< orphan*/  ood_kind; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; void* repos_relpath; int /*<<< orphan*/  ood_changed_date; scalar_t__ ood_changed_rev; int /*<<< orphan*/  kind; int /*<<< orphan*/  const* repos_lock; } ;
typedef  TYPE_8__ svn_wc_status3_t ;
struct TYPE_21__ {TYPE_8__ s; } ;
typedef  TYPE_9__ svn_wc__internal_status_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct file_baton {char const* repos_relpath; char const* ood_changed_author; int /*<<< orphan*/  ood_kind; TYPE_7__* edit_baton; int /*<<< orphan*/  ood_changed_date; scalar_t__ ood_changed_rev; TYPE_1__* dir_baton; } ;
struct dir_baton {char const* repos_relpath; char const* ood_changed_author; int /*<<< orphan*/  ood_changed_date; scalar_t__ ood_changed_rev; int /*<<< orphan*/  ood_kind; TYPE_4__* edit_baton; int /*<<< orphan*/ * statii; } ;
typedef  enum svn_wc_status_kind { ____Placeholder_svn_wc_status_kind } svn_wc_status_kind ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_19__ {TYPE_6__* anchor_status; } ;
struct TYPE_17__ {int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; } ;
struct TYPE_18__ {TYPE_5__ s; } ;
struct TYPE_16__ {TYPE_3__* anchor_status; } ;
struct TYPE_14__ {int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; } ;
struct TYPE_15__ {TYPE_2__ s; } ;
struct TYPE_13__ {int /*<<< orphan*/ * statii; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  internal_status (TYPE_9__**,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 TYPE_8__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,void*,TYPE_8__*) ; 
 void* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svn_wc_status_added ; 
 scalar_t__ svn_wc_status_deleted ; 
 int svn_wc_status_replaced ; 

__attribute__((used)) static svn_error_t *
tweak_statushash(void *baton,
                 void *this_dir_baton,
                 svn_boolean_t is_dir_baton,
                 svn_wc__db_t *db,
                 svn_boolean_t check_working_copy,
                 const char *local_abspath,
                 enum svn_wc_status_kind repos_node_status,
                 enum svn_wc_status_kind repos_text_status,
                 enum svn_wc_status_kind repos_prop_status,
                 svn_revnum_t deleted_rev,
                 const svn_lock_t *repos_lock,
                 apr_pool_t *scratch_pool)
{
  svn_wc_status3_t *statstruct;
  apr_pool_t *pool;
  apr_hash_t *statushash;

  if (is_dir_baton)
    statushash = ((struct dir_baton *) baton)->statii;
  else
    statushash = ((struct file_baton *) baton)->dir_baton->statii;
  pool = apr_hash_pool_get(statushash);

  /* Is PATH already a hash-key? */
  statstruct = svn_hash_gets(statushash, local_abspath);

  /* If not, make it so. */
  if (! statstruct)
    {
      svn_wc__internal_status_t *i_stat;
      /* If this item isn't being added, then we're most likely
         dealing with a non-recursive (or at least partially
         non-recursive) working copy.  Due to bugs in how the client
         reports the state of non-recursive working copies, the
         repository can send back responses about paths that don't
         even exist locally.  Our best course here is just to ignore
         those responses.  After all, if the client had reported
         correctly in the first, that path would either be mentioned
         as an 'add' or not mentioned at all, depending on how we
         eventually fix the bugs in non-recursivity.  See issue
         #2122 for details. */
      if (repos_node_status != svn_wc_status_added)
        return SVN_NO_ERROR;

      /* Use the public API to get a statstruct, and put it into the hash. */
      SVN_ERR(internal_status(&i_stat, db, local_abspath,
                              check_working_copy, pool, scratch_pool));
      statstruct = &i_stat->s;
      statstruct->repos_lock = repos_lock;
      svn_hash_sets(statushash, apr_pstrdup(pool, local_abspath), statstruct);
    }

  /* Merge a repos "delete" + "add" into a single "replace". */
  if ((repos_node_status == svn_wc_status_added)
      && (statstruct->repos_node_status == svn_wc_status_deleted))
    repos_node_status = svn_wc_status_replaced;

  /* Tweak the structure's repos fields. */
  if (repos_node_status)
    statstruct->repos_node_status = repos_node_status;
  if (repos_text_status)
    statstruct->repos_text_status = repos_text_status;
  if (repos_prop_status)
    statstruct->repos_prop_status = repos_prop_status;

  /* Copy out-of-date info. */
  if (is_dir_baton)
    {
      struct dir_baton *b = this_dir_baton;

      if (!statstruct->repos_relpath && b->repos_relpath)
        {
          if (statstruct->repos_node_status == svn_wc_status_deleted)
            {
              /* When deleting PATH, BATON is for PATH's parent,
                 so we must construct PATH's real statstruct->url. */
              statstruct->repos_relpath =
                            svn_relpath_join(b->repos_relpath,
                                             svn_dirent_basename(local_abspath,
                                                                 NULL),
                                             pool);
            }
          else
            statstruct->repos_relpath = apr_pstrdup(pool, b->repos_relpath);

          statstruct->repos_root_url =
                              b->edit_baton->anchor_status->s.repos_root_url;
          statstruct->repos_uuid =
                              b->edit_baton->anchor_status->s.repos_uuid;
        }

      /* The last committed date, and author for deleted items
         isn't available. */
      if (statstruct->repos_node_status == svn_wc_status_deleted)
        {
          statstruct->ood_kind = statstruct->kind;

          /* Pre 1.5 servers don't provide the revision a path was deleted.
             So we punt and use the last committed revision of the path's
             parent, which has some chance of being correct.  At worse it
             is a higher revision than the path was deleted, but this is
             better than nothing... */
          if (deleted_rev == SVN_INVALID_REVNUM)
            statstruct->ood_changed_rev =
              ((struct dir_baton *) baton)->ood_changed_rev;
          else
            statstruct->ood_changed_rev = deleted_rev;
        }
      else
        {
          statstruct->ood_kind = b->ood_kind;
          statstruct->ood_changed_rev = b->ood_changed_rev;
          statstruct->ood_changed_date = b->ood_changed_date;
          if (b->ood_changed_author)
            statstruct->ood_changed_author =
              apr_pstrdup(pool, b->ood_changed_author);
        }

    }
  else
    {
      struct file_baton *b = baton;
      statstruct->ood_changed_rev = b->ood_changed_rev;
      statstruct->ood_changed_date = b->ood_changed_date;
      if (!statstruct->repos_relpath && b->repos_relpath)
        {
          statstruct->repos_relpath = apr_pstrdup(pool, b->repos_relpath);
          statstruct->repos_root_url =
                          b->edit_baton->anchor_status->s.repos_root_url;
          statstruct->repos_uuid =
                          b->edit_baton->anchor_status->s.repos_uuid;
        }
      statstruct->ood_kind = b->ood_kind;
      if (b->ood_changed_author)
        statstruct->ood_changed_author =
          apr_pstrdup(pool, b->ood_changed_author);
    }
  return SVN_NO_ERROR;
}