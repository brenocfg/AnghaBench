#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks3_wrapper_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/  anchor; TYPE_1__* callbacks3; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* dir_closed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_4to3_dir_closed(svn_wc_notify_state_t *contentstate,
                     svn_wc_notify_state_t *propstate,
                     svn_boolean_t *tree_conflicted,
                     const char *path,
                     svn_boolean_t dir_was_added,
                     void *diff_baton,
                     apr_pool_t *scratch_pool)
{
  struct diff_callbacks3_wrapper_baton *b = diff_baton;
  svn_wc_adm_access_t *adm_access;

  adm_access = svn_wc__adm_retrieve_internal2(
                        b->db,
                        svn_dirent_join(b->anchor_abspath, path, scratch_pool),
                        scratch_pool);

  return b->callbacks3->dir_closed(adm_access, contentstate, propstate,
                                   tree_conflicted,
                                   svn_dirent_join(b->anchor, path,
                                                     scratch_pool),
                                   b->baton);
}