#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_2__* baton; } ;
typedef  TYPE_3__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* dir_closed ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_dir_closed(const char *relpath,
                const svn_diff_source_t *left_source,
                const svn_diff_source_t *right_source,
                void *dir_baton,
                const svn_diff_tree_processor_t *processor,
                apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wb = processor->baton;

  /* No previous implementations provided these arguments, so we
     are not providing them either */
  SVN_ERR(wb->callbacks->dir_closed(NULL, NULL, NULL,
                                    relpath,
                                    FALSE /* added */,
                                    wb->callback_baton,
                                    scratch_pool));

return SVN_NO_ERROR;
}