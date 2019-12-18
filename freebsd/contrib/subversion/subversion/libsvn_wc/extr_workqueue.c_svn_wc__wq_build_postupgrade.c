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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  OP_POSTUPGRADE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__wq_build_postupgrade(svn_skel_t **work_item,
                             apr_pool_t *result_pool)
{
  *work_item = svn_skel__make_empty_list(result_pool);

  svn_skel__prepend_str(OP_POSTUPGRADE, *work_item, result_pool);

  return SVN_NO_ERROR;
}