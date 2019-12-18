#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct svn_diff_tree_processor_t {TYPE_2__* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* dir_props_changed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  wrap_dir_closed (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,struct svn_diff_tree_processor_t const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_dir_changed(const char *relpath,
                 const svn_diff_source_t *left_source,
                 const svn_diff_source_t *right_source,
                 /*const*/ apr_hash_t *left_props,
                 /*const*/ apr_hash_t *right_props,
                 const apr_array_header_t *prop_changes,
                 void *dir_baton,
                 const struct svn_diff_tree_processor_t *processor,
                 apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wb = processor->baton;
  svn_boolean_t tree_conflicted = FALSE;
  svn_wc_notify_state_t prop_state = svn_wc_notify_state_inapplicable;

  assert(left_source && right_source);

  SVN_ERR(wb->callbacks->dir_props_changed(&prop_state, &tree_conflicted,
                                           relpath,
                                           FALSE /* dir_was_added */,
                                           prop_changes,
                                           left_props,
                                           wb->callback_baton,
                                           scratch_pool));

  /* And call dir_closed, etc */
  SVN_ERR(wrap_dir_closed(relpath, left_source, right_source,
                          dir_baton, processor,
                          scratch_pool));
  return SVN_NO_ERROR;
}