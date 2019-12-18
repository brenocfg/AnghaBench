#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct node_state_t {char const* local_abspath; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * baton; struct node_state_t* parent; void* right_src; void* left_src; void* relpath; void* skip_children; void* skip; } ;
struct diff_baton {TYPE_7__* processor; int /*<<< orphan*/  db; struct node_state_t* cur; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {TYPE_1__* (* dir_opened ) (int /*<<< orphan*/ **,void**,void**,void*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 TYPE_1__* SVN_NO_ERROR ; 
 void* TRUE ; 
 struct node_state_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* stub1 (int /*<<< orphan*/ **,void**,void**,void*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_diff__source_create (scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_child (char const*,char const*,int /*<<< orphan*/ *) ; 
 void* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ensure_state(struct diff_baton *eb,
             const char *local_abspath,
             svn_boolean_t recursive_skip,
             apr_pool_t *scratch_pool)
{
  struct node_state_t *ns;
  apr_pool_t *ns_pool;
  if (!eb->cur)
    {
      const char *relpath;

      relpath = svn_dirent_skip_ancestor(eb->anchor_abspath, local_abspath);
      if (! relpath)
        return SVN_NO_ERROR;

      /* Don't recurse on the anchor, as that might loop infinitely because
            svn_dirent_dirname("/",...)   -> "/"
            svn_dirent_dirname("C:/",...) -> "C:/" (Windows) */
      if (*relpath)
        SVN_ERR(ensure_state(eb,
                             svn_dirent_dirname(local_abspath, scratch_pool),
                             FALSE,
                             scratch_pool));
    }
  else if (svn_dirent_is_child(eb->cur->local_abspath, local_abspath, NULL))
    SVN_ERR(ensure_state(eb, svn_dirent_dirname(local_abspath, scratch_pool),
                         FALSE,
                         scratch_pool));
  else
    return SVN_NO_ERROR;

  if (eb->cur && eb->cur->skip_children)
    return SVN_NO_ERROR;

  ns_pool = svn_pool_create(eb->cur ? eb->cur->pool : eb->pool);
  ns = apr_pcalloc(ns_pool, sizeof(*ns));

  ns->pool = ns_pool;
  ns->local_abspath = apr_pstrdup(ns_pool, local_abspath);
  ns->relpath = svn_dirent_skip_ancestor(eb->anchor_abspath, ns->local_abspath);
  ns->parent = eb->cur;
  eb->cur = ns;

  if (recursive_skip)
    {
      ns->skip = TRUE;
      ns->skip_children = TRUE;
      return SVN_NO_ERROR;
    }

  {
    svn_revnum_t revision;
    svn_error_t *err;

    err = svn_wc__db_base_get_info(NULL, NULL, &revision, NULL, NULL, NULL,
                                   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                   NULL, NULL, NULL,
                                   eb->db, local_abspath,
                                   scratch_pool, scratch_pool);

    if (err)
      {
        if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
          return svn_error_trace(err);
        svn_error_clear(err);

        revision = 0; /* Use original revision? */
      }
    ns->left_src = svn_diff__source_create(revision, ns->pool);
    ns->right_src = svn_diff__source_create(SVN_INVALID_REVNUM, ns->pool);

    SVN_ERR(eb->processor->dir_opened(&ns->baton, &ns->skip,
                                      &ns->skip_children,
                                      ns->relpath,
                                      ns->left_src,
                                      ns->right_src,
                                      NULL /* copyfrom_source */,
                                      ns->parent ? ns->parent->baton : NULL,
                                      eb->processor,
                                      ns->pool, scratch_pool));
  }

  return SVN_NO_ERROR;
}