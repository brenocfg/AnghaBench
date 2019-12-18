#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ next_patch_offset; int /*<<< orphan*/  apr_file; } ;
typedef  TYPE_1__ svn_patch_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_open_patch_file(svn_patch_file_t **patch_file,
                         const char *local_abspath,
                         apr_pool_t *result_pool)
{
  svn_patch_file_t *p;

  p = apr_palloc(result_pool, sizeof(*p));
  SVN_ERR(svn_io_file_open(&p->apr_file, local_abspath,
                           APR_READ | APR_BUFFERED, APR_OS_DEFAULT,
                           result_pool));
  p->next_patch_offset = 0;
  *patch_file = p;

  return SVN_NO_ERROR;
}