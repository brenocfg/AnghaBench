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
struct TYPE_10__ {char const* empty_file; int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_2__* baton; } ;
typedef  TYPE_3__ svn_diff_tree_processor_t ;
struct TYPE_12__ {int /*<<< orphan*/  revision; int /*<<< orphan*/ * repos_relpath; } ;
typedef  TYPE_4__ svn_diff_source_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* file_added ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  wrap_ensure_empty_file (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_file_added(const char *relpath,
                const svn_diff_source_t *copyfrom_source,
                const svn_diff_source_t *right_source,
                const char *copyfrom_file,
                const char *right_file,
                /*const*/ apr_hash_t *copyfrom_props,
                /*const*/ apr_hash_t *right_props,
                void *file_baton,
                const svn_diff_tree_processor_t *processor,
                apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wb = processor->baton;
  svn_boolean_t tree_conflicted = FALSE;
  svn_wc_notify_state_t state = svn_wc_notify_state_inapplicable;
  svn_wc_notify_state_t prop_state = svn_wc_notify_state_inapplicable;
  apr_array_header_t *prop_changes;

  if (! copyfrom_props)
    copyfrom_props = apr_hash_make(scratch_pool);

  SVN_ERR(svn_prop_diffs(&prop_changes, right_props, copyfrom_props,
                         scratch_pool));

  if (! copyfrom_source)
    SVN_ERR(wrap_ensure_empty_file(wb, scratch_pool));

  SVN_ERR(wb->callbacks->file_added(&state, &prop_state, &tree_conflicted,
                                    relpath,
                                    copyfrom_source
                                        ? copyfrom_file
                                        : wb->empty_file,
                                    right_file,
                                    0,
                                    right_source->revision,
                                    copyfrom_props
                                     ? svn_prop_get_value(copyfrom_props,
                                                          SVN_PROP_MIME_TYPE)
                                     : NULL,
                                    right_props
                                     ? svn_prop_get_value(right_props,
                                                          SVN_PROP_MIME_TYPE)
                                     : NULL,
                                    copyfrom_source
                                            ? copyfrom_source->repos_relpath
                                            : NULL,
                                    copyfrom_source
                                            ? copyfrom_source->revision
                                            : SVN_INVALID_REVNUM,
                                    prop_changes, copyfrom_props,
                                    wb->callback_baton,
                                    scratch_pool));
  return SVN_NO_ERROR;
}