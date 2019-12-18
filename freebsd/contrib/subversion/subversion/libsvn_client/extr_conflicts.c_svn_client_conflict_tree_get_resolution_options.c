#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  assert_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_accept_current_wc_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_add_ignore (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_added_dir_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_added_dir_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_added_dir_replace_and_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_added_file_replace_and_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_added_file_text_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_delete_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_delete_ignore (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_dir_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_incoming_move_file_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_local_move_file_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_update_move_destination (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configure_option_update_raise_moved_away_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_postpone ; 
 int /*<<< orphan*/  svn_client_conflict_option_postpone ; 

svn_error_t *
svn_client_conflict_tree_get_resolution_options(apr_array_header_t **options,
                                                svn_client_conflict_t *conflict,
                                                svn_client_ctx_t *ctx,
                                                apr_pool_t *result_pool,
                                                apr_pool_t *scratch_pool)
{
  SVN_ERR(assert_tree_conflict(conflict, scratch_pool));

  *options = apr_array_make(result_pool, 2,
                            sizeof(svn_client_conflict_option_t *));

  /* Add postpone option. */
  add_resolution_option(*options, conflict,
                        svn_client_conflict_option_postpone,
                        _("Postpone"),
                        _("skip this conflict and leave it unresolved"),
                        resolve_postpone);

  /* Add an option which marks the conflict resolved. */
  SVN_ERR(configure_option_accept_current_wc_state(conflict, *options));

  /* Configure options which offer automatic resolution. */
  SVN_ERR(configure_option_update_move_destination(conflict, *options));
  SVN_ERR(configure_option_update_raise_moved_away_children(conflict,
                                                            *options));
  SVN_ERR(configure_option_incoming_add_ignore(conflict, ctx, *options,
                                               scratch_pool));
  SVN_ERR(configure_option_incoming_added_file_text_merge(conflict, ctx,
                                                          *options,
                                                          scratch_pool));
  SVN_ERR(configure_option_incoming_added_file_replace_and_merge(conflict,
                                                                 ctx,
                                                                 *options,
                                                                 scratch_pool));
  SVN_ERR(configure_option_incoming_added_dir_merge(conflict, ctx,
                                                    *options,
                                                    scratch_pool));
  SVN_ERR(configure_option_incoming_added_dir_replace(conflict, ctx,
                                                      *options,
                                                      scratch_pool));
  SVN_ERR(configure_option_incoming_added_dir_replace_and_merge(conflict,
                                                                ctx,
                                                                *options,
                                                                scratch_pool));
  SVN_ERR(configure_option_incoming_delete_ignore(conflict, ctx, *options,
                                                  scratch_pool));
  SVN_ERR(configure_option_incoming_delete_accept(conflict, ctx, *options,
                                                  scratch_pool));
  SVN_ERR(configure_option_incoming_move_file_merge(conflict, ctx, *options,
                                                    scratch_pool));
  SVN_ERR(configure_option_incoming_dir_merge(conflict, ctx, *options,
                                              scratch_pool));
  SVN_ERR(configure_option_local_move_file_merge(conflict, ctx, *options,
                                                 scratch_pool));

  return SVN_NO_ERROR;
}