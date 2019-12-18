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
struct TYPE_10__ {int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_2__* baton; } ;
typedef  TYPE_3__ svn_diff_tree_processor_t ;
struct TYPE_12__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_4__ svn_diff_source_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* file_changed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  wrap_ensure_empty_file (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_file_changed(const char *relpath,
                  const svn_diff_source_t *left_source,
                  const svn_diff_source_t *right_source,
                  const char *left_file,
                  const char *right_file,
                  /*const*/ apr_hash_t *left_props,
                  /*const*/ apr_hash_t *right_props,
                  svn_boolean_t file_modified,
                  const apr_array_header_t *prop_changes,
                  void *file_baton,
                  const svn_diff_tree_processor_t *processor,
                  apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wb = processor->baton;
  svn_boolean_t tree_conflicted = FALSE;
  svn_wc_notify_state_t state = svn_wc_notify_state_inapplicable;
  svn_wc_notify_state_t prop_state = svn_wc_notify_state_inapplicable;

  SVN_ERR(wrap_ensure_empty_file(wb, scratch_pool));

  assert(left_source && right_source);

  SVN_ERR(wb->callbacks->file_changed(&state, &prop_state, &tree_conflicted,
                                      relpath,
                                      file_modified ? left_file : NULL,
                                      file_modified ? right_file : NULL,
                                      left_source->revision,
                                      right_source->revision,
                                      left_props
                                       ? svn_prop_get_value(left_props,
                                                            SVN_PROP_MIME_TYPE)
                                       : NULL,
                                      right_props
                                       ? svn_prop_get_value(right_props,
                                                            SVN_PROP_MIME_TYPE)
                                       : NULL,
                                       prop_changes,
                                      left_props,
                                      wb->callback_baton,
                                      scratch_pool));
  return SVN_NO_ERROR;
}