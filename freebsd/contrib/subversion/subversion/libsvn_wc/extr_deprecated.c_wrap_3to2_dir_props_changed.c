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
struct diff_callbacks2_wrapper_baton {int /*<<< orphan*/  baton; TYPE_1__* callbacks2; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* dir_props_changed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
wrap_3to2_dir_props_changed(svn_wc_adm_access_t *adm_access,
                            svn_wc_notify_state_t *state,
                            svn_boolean_t *tree_conflicted,
                            const char *path,
                            const apr_array_header_t *propchanges,
                            apr_hash_t *originalprops,
                            void *diff_baton)
{
  struct diff_callbacks2_wrapper_baton *b = diff_baton;

  if (tree_conflicted)
    *tree_conflicted = FALSE;

  return b->callbacks2->dir_props_changed(adm_access, state, path, propchanges,
                                          originalprops, b->baton);
}