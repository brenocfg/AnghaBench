#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  result_pool; scalar_t__ empty_file; } ;
typedef  TYPE_1__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_ensure_empty_file(wc_diff_wrap_baton_t *wb,
                       apr_pool_t *scratch_pool)
{
  if (wb->empty_file)
    return SVN_NO_ERROR;

  /* Create a unique file in the tempdir */
  SVN_ERR(svn_io_open_unique_file3(NULL, &wb->empty_file, NULL,
                                   svn_io_file_del_on_pool_cleanup,
                                   wb->result_pool, scratch_pool));

  return SVN_NO_ERROR;
}