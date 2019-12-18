#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int kind; int actual_kind; int node_status; int text_status; int prop_status; int repos_node_status; int repos_text_status; int repos_prop_status; char const* moved_from_abspath; int /*<<< orphan*/  file_external; void* moved_to_abspath; void* changelist; void* versioned; void* conflicted; int /*<<< orphan*/  locked; TYPE_5__* lock; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/ * ood_changed_author; scalar_t__ ood_changed_date; int /*<<< orphan*/  ood_changed_rev; scalar_t__ ood_kind; int /*<<< orphan*/  changed_date; void* changed_author; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  revision; TYPE_5__ const* repos_lock; void* copied; void* switched; scalar_t__ filesize; int /*<<< orphan*/  depth; } ;
typedef  TYPE_3__ svn_wc_status3_t ;
struct TYPE_23__ {scalar_t__ op_root; int /*<<< orphan*/  has_descendants; TYPE_3__ s; } ;
typedef  TYPE_4__ svn_wc__internal_status_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_24__ {int /*<<< orphan*/  creation_date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; int /*<<< orphan*/  path; } ;
typedef  TYPE_5__ svn_lock_t ;
struct TYPE_25__ {scalar_t__ kind; scalar_t__ filesize; scalar_t__ mtime; scalar_t__ special; } ;
typedef  TYPE_6__ svn_io_dirent2_t ;
struct TYPE_26__ {scalar_t__ apr_err; } ;
typedef  TYPE_7__ svn_error_t ;
typedef  void* svn_boolean_t ;
struct svn_wc__db_info_t {scalar_t__ status; int kind; int special; scalar_t__ recorded_size; scalar_t__ recorded_time; int /*<<< orphan*/  file_external; TYPE_2__* moved_to; scalar_t__ changelist; int /*<<< orphan*/  locked; TYPE_1__* lock; int /*<<< orphan*/  changed_date; scalar_t__ changed_author; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  revnum; int /*<<< orphan*/  depth; scalar_t__ op_root; int /*<<< orphan*/  has_descendants; scalar_t__ moved_here; scalar_t__ have_more_work; scalar_t__ have_base; void* copied; void* conflicted; int /*<<< orphan*/  has_checksum; scalar_t__ had_props; scalar_t__ props_mod; scalar_t__ incomplete; int /*<<< orphan*/  repos_relpath; } ;
typedef  enum svn_wc_status_kind { ____Placeholder_svn_wc_status_kind } svn_wc_status_kind ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_21__ {scalar_t__ moved_to_abspath; } ;
struct TYPE_20__ {int /*<<< orphan*/  date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_ACCESS_DENIED ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 scalar_t__ SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_7__* SVN_NO_ERROR ; 
 void* TRUE ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  get_repos_root_url_relpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct svn_wc__db_info_t const*,char const*,char const*,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_7__*) ; 
 TYPE_7__* svn_error_trace (TYPE_7__*) ; 
 TYPE_5__* svn_lock_create (int /*<<< orphan*/ *) ; 
#define  svn_node_dir 131 
#define  svn_node_file 130 
 scalar_t__ svn_node_none ; 
#define  svn_node_symlink 129 
#define  svn_node_unknown 128 
 char* svn_relpath_skip_ancestor (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_info_below_working (void**,void**,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_deletion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_7__* svn_wc__db_scan_moved (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 int /*<<< orphan*/  svn_wc__internal_conflicted_p (void**,void**,void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_7__* svn_wc__internal_file_modified_p (void**,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ; 
 int svn_wc_status_added ; 
 int svn_wc_status_deleted ; 
 int svn_wc_status_incomplete ; 
 int svn_wc_status_missing ; 
 int svn_wc_status_modified ; 
 int svn_wc_status_none ; 
 int svn_wc_status_normal ; 
 int svn_wc_status_obstructed ; 
 int svn_wc_status_replaced ; 

__attribute__((used)) static svn_error_t *
assemble_status(svn_wc__internal_status_t **status,
                svn_wc__db_t *db,
                const char *local_abspath,
                const char *parent_repos_root_url,
                const char *parent_repos_relpath,
                const char *parent_repos_uuid,
                const struct svn_wc__db_info_t *info,
                const svn_io_dirent2_t *dirent,
                svn_boolean_t get_all,
                svn_boolean_t ignore_text_mods,
                svn_boolean_t check_working_copy,
                const svn_lock_t *repos_lock,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  svn_wc__internal_status_t *inner_stat;
  svn_wc_status3_t *stat;
  svn_boolean_t switched_p = FALSE;
  svn_boolean_t copied = FALSE;
  svn_boolean_t conflicted;
  const char *moved_from_abspath = NULL;

  /* Defaults for two main variables. */
  enum svn_wc_status_kind node_status = svn_wc_status_normal;
  enum svn_wc_status_kind text_status = svn_wc_status_normal;
  enum svn_wc_status_kind prop_status = svn_wc_status_none;


  if (!info->repos_relpath || !parent_repos_relpath)
    switched_p = FALSE;
  else
    {
      /* A node is switched if it doesn't have the implied repos_relpath */
      const char *name = svn_relpath_skip_ancestor(parent_repos_relpath,
                                                   info->repos_relpath);
      switched_p = !name || (strcmp(name,
                                    svn_dirent_basename(local_abspath, NULL))
                             != 0);
    }

  if (info->status == svn_wc__db_status_incomplete || info->incomplete)
    {
      /* Highest precedence.  */
      node_status = svn_wc_status_incomplete;
    }
  else if (info->status == svn_wc__db_status_deleted)
    {
      node_status = svn_wc_status_deleted;

      if (!info->have_base || info->have_more_work || info->copied)
        copied = TRUE;
      else if (!info->have_more_work && info->have_base)
        copied = FALSE;
      else
        {
          const char *work_del_abspath;

          /* Find out details of our deletion.  */
          SVN_ERR(svn_wc__db_scan_deletion(NULL, NULL,
                                           &work_del_abspath, NULL,
                                           db, local_abspath,
                                           scratch_pool, scratch_pool));
          if (work_del_abspath)
            copied = TRUE; /* Working deletion */
        }
    }
  else if (check_working_copy)
    {
      /* Examine whether our target is missing or obstructed. To detect
       * obstructions, we have to look at the on-disk status in DIRENT. */
      svn_node_kind_t expected_kind = (info->kind == svn_node_dir)
                                        ? svn_node_dir
                                        : svn_node_file;

      if (!dirent || dirent->kind != expected_kind)
        {
          /* A present or added node should be on disk, so it is
             reported missing or obstructed.  */
          if (!dirent || dirent->kind == svn_node_none)
            node_status = svn_wc_status_missing;
          else
            node_status = svn_wc_status_obstructed;
        }
    }

  /* Does the node have props? */
  if (info->status != svn_wc__db_status_deleted)
    {
      if (info->props_mod)
        prop_status = svn_wc_status_modified;
      else if (info->had_props)
        prop_status = svn_wc_status_normal;
    }

  /* If NODE_STATUS is still normal, after the above checks, then
     we should proceed to refine the status.

     If it was changed, then the subdir is incomplete or missing/obstructed.
   */
  if (info->kind != svn_node_dir
      && node_status == svn_wc_status_normal)
    {
      svn_boolean_t text_modified_p = FALSE;

      /* Implement predecence rules: */

      /* 1. Set the two main variables to "discovered" values first (M, C).
            Together, these two stati are of lowest precedence, and C has
            precedence over M. */

      /* If the entry is a file, check for textual modifications */
      if ((info->kind == svn_node_file
          || info->kind == svn_node_symlink)
#ifdef HAVE_SYMLINK
             && (info->special == (dirent && dirent->special))
#endif /* HAVE_SYMLINK */
          )
        {
          /* If the on-disk dirent exactly matches the expected state
             skip all operations in svn_wc__internal_text_modified_p()
             to avoid an extra filestat for every file, which can be
             expensive on network drives as a filestat usually can't
             be cached there */
          if (!info->has_checksum)
            text_modified_p = TRUE; /* Local addition -> Modified */
          else if (ignore_text_mods
                  ||(dirent
                     && info->recorded_size != SVN_INVALID_FILESIZE
                     && info->recorded_time != 0
                     && info->recorded_size == dirent->filesize
                     && info->recorded_time == dirent->mtime))
            text_modified_p = FALSE;
          else
            {
              svn_error_t *err;
              err = svn_wc__internal_file_modified_p(&text_modified_p,
                                                     db, local_abspath,
                                                     FALSE, scratch_pool);

              if (err)
                {
                  if (err->apr_err != SVN_ERR_WC_PATH_ACCESS_DENIED)
                    return svn_error_trace(err);

                  /* An access denied is very common on Windows when another
                     application has the file open.  Previously we ignored
                     this error in svn_wc__text_modified_internal_p, where it
                     should have really errored. */
                  svn_error_clear(err);
                  text_modified_p = TRUE;
                }
            }
        }
#ifdef HAVE_SYMLINK
      else if (info->special != (dirent && dirent->special))
        node_status = svn_wc_status_obstructed;
#endif /* HAVE_SYMLINK */

      if (text_modified_p)
        text_status = svn_wc_status_modified;
    }

  conflicted = info->conflicted;
  if (conflicted)
    {
      svn_boolean_t text_conflicted, prop_conflicted, tree_conflicted;

      /* ### Check if the conflict was resolved by removing the marker files.
         ### This should really be moved to the users of this API */
      SVN_ERR(svn_wc__internal_conflicted_p(&text_conflicted, &prop_conflicted,
                                            &tree_conflicted,
                                            db, local_abspath, scratch_pool));

      if (!text_conflicted && !prop_conflicted && !tree_conflicted)
        conflicted = FALSE;
    }

  if (node_status == svn_wc_status_normal)
    {
      /* 2. Possibly overwrite the text_status variable with "scheduled"
            states from the entry (A, D, R).  As a group, these states are
            of medium precedence.  They also override any C or M that may
            be in the prop_status field at this point, although they do not
            override a C text status.*/
      if (info->status == svn_wc__db_status_added)
        {
          copied = info->copied;
          if (!info->op_root)
            { /* Keep status normal */ }
          else if (!info->have_base && !info->have_more_work)
            {
              /* Simple addition or copy, no replacement */
              node_status = svn_wc_status_added;
            }
          else
            {
              svn_wc__db_status_t below_working;
              svn_boolean_t have_base, have_work;

              SVN_ERR(svn_wc__db_info_below_working(&have_base, &have_work,
                                                    &below_working,
                                                    db, local_abspath,
                                                    scratch_pool));

              /* If the node is not present or deleted (read: not present
                 in working), then the node is not a replacement */
              if (below_working != svn_wc__db_status_not_present
                  && below_working != svn_wc__db_status_deleted)
                {
                  node_status = svn_wc_status_replaced;
                }
              else
                node_status = svn_wc_status_added;
            }

          /* Get moved-from info (only for potential op-roots of a move). */
          if (info->moved_here && info->op_root)
            {
              svn_error_t *err;
              err = svn_wc__db_scan_moved(&moved_from_abspath, NULL, NULL, NULL,
                                          db, local_abspath,
                                          result_pool, scratch_pool);

              if (err)
                {
                  if (err->apr_err != SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
                    return svn_error_trace(err);

                  svn_error_clear(err);
                  /* We are no longer moved... So most likely we are somehow
                     changing the db for things like resolving conflicts. */

                  moved_from_abspath = NULL;
                }
            }
        }
    }


  if (node_status == svn_wc_status_normal)
    node_status = text_status;

  if (node_status == svn_wc_status_normal
      && prop_status != svn_wc_status_none)
    node_status = prop_status;

  /* 5. Easy out:  unless we're fetching -every- node, don't bother
     to allocate a struct for an uninteresting node.

     This filter should match the filter in is_sendable_status() */
  if (! get_all)
    if (((node_status == svn_wc_status_none)
         || (node_status == svn_wc_status_normal)
         || (node_status == svn_wc_status_deleted && !info->op_root))

        && (! switched_p)
        && (! info->locked)
        && (! info->lock)
        && (! repos_lock)
        && (! info->changelist)
        && (! conflicted)
        && (! info->moved_to))
      {
        *status = NULL;
        return SVN_NO_ERROR;
      }

  /* 6. Build and return a status structure. */

  inner_stat = apr_pcalloc(result_pool, sizeof(*inner_stat));
  stat = &inner_stat->s;
  inner_stat->has_descendants = info->has_descendants;
  inner_stat->op_root = info->op_root;

  switch (info->kind)
    {
      case svn_node_dir:
        stat->kind = svn_node_dir;
        break;
      case svn_node_file:
      case svn_node_symlink:
        stat->kind = svn_node_file;
        break;
      case svn_node_unknown:
      default:
        stat->kind = svn_node_unknown;
    }
  stat->depth = info->depth;

  if (dirent)
    {
      stat->filesize = (dirent->kind == svn_node_file)
                            ? dirent->filesize
                            : SVN_INVALID_FILESIZE;
      stat->actual_kind = dirent->special ? svn_node_symlink
                                          : dirent->kind;
    }
  else
    {
      stat->filesize = SVN_INVALID_FILESIZE;
      stat->actual_kind = ignore_text_mods ? svn_node_unknown
                                           : svn_node_none;
    }

  stat->node_status = node_status;
  stat->text_status = text_status;
  stat->prop_status = prop_status;
  stat->repos_node_status = svn_wc_status_none;   /* default */
  stat->repos_text_status = svn_wc_status_none;   /* default */
  stat->repos_prop_status = svn_wc_status_none;   /* default */
  stat->switched = switched_p;
  stat->copied = copied;
  stat->repos_lock = repos_lock;
  stat->revision = info->revnum;
  stat->changed_rev = info->changed_rev;
  if (info->changed_author)
    stat->changed_author = apr_pstrdup(result_pool, info->changed_author);
  stat->changed_date = info->changed_date;

  stat->ood_kind = svn_node_none;
  stat->ood_changed_rev = SVN_INVALID_REVNUM;
  stat->ood_changed_date = 0;
  stat->ood_changed_author = NULL;

  SVN_ERR(get_repos_root_url_relpath(&stat->repos_relpath,
                                     &stat->repos_root_url,
                                     &stat->repos_uuid, info,
                                     parent_repos_relpath,
                                     parent_repos_root_url,
                                     parent_repos_uuid,
                                     db, local_abspath,
                                     result_pool, scratch_pool));

  if (info->lock)
    {
      svn_lock_t *lck = svn_lock_create(result_pool);
      lck->path = stat->repos_relpath;
      lck->token = info->lock->token;
      lck->owner = info->lock->owner;
      lck->comment = info->lock->comment;
      lck->creation_date = info->lock->date;
      stat->lock = lck;
    }
  else
    stat->lock = NULL;

  stat->locked = info->locked;
  stat->conflicted = conflicted;
  stat->versioned = TRUE;
  if (info->changelist)
    stat->changelist = apr_pstrdup(result_pool, info->changelist);

  stat->moved_from_abspath = moved_from_abspath;

  /* ### TODO: Handle multiple moved_to values properly */
  if (info->moved_to)
    stat->moved_to_abspath = apr_pstrdup(result_pool,
                                         info->moved_to->moved_to_abspath);

  stat->file_external = info->file_external;

  *status = inner_stat;

  return SVN_NO_ERROR;
}