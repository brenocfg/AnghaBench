#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; int /*<<< orphan*/  walk_deleted_dirs; } ;
typedef  TYPE_2__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_2__* baton; } ;
typedef  TYPE_3__ svn_diff_tree_processor_t ;
struct TYPE_12__ {int /*<<< orphan*/  revision; int /*<<< orphan*/ * repos_relpath; } ;
typedef  TYPE_4__ svn_diff_source_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* dir_added ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_opened ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 

__attribute__((used)) static svn_error_t *
wrap_dir_opened(void **new_dir_baton,
                svn_boolean_t *skip,
                svn_boolean_t *skip_children,
                const char *relpath,
                const svn_diff_source_t *left_source,
                const svn_diff_source_t *right_source,
                const svn_diff_source_t *copyfrom_source,
                void *parent_dir_baton,
                const svn_diff_tree_processor_t *processor,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wb = processor->baton;
  svn_boolean_t tree_conflicted = FALSE;

  assert(left_source || right_source);      /* Must exist at one point. */
  assert(!left_source || !copyfrom_source); /* Either existed or added. */

  /* Maybe store state and tree_conflicted in baton? */
  if (left_source != NULL)
    {
      /* Open for change or delete */
      SVN_ERR(wb->callbacks->dir_opened(&tree_conflicted, skip, skip_children,
                                        relpath,
                                        right_source
                                            ? right_source->revision
                                            : (left_source
                                                    ? left_source->revision
                                                    : SVN_INVALID_REVNUM),
                                        wb->callback_baton,
                                        scratch_pool));

      if (! right_source && !wb->walk_deleted_dirs)
        *skip_children = TRUE;
    }
  else /* left_source == NULL -> Add */
    {
      svn_wc_notify_state_t state = svn_wc_notify_state_inapplicable;
      SVN_ERR(wb->callbacks->dir_added(&state, &tree_conflicted,
                                       skip, skip_children,
                                       relpath,
                                       right_source->revision,
                                       copyfrom_source
                                            ? copyfrom_source->repos_relpath
                                            : NULL,
                                       copyfrom_source
                                            ? copyfrom_source->revision
                                            : SVN_INVALID_REVNUM,
                                       wb->callback_baton,
                                       scratch_pool));
    }

  *new_dir_baton = NULL;

  return SVN_NO_ERROR;
}