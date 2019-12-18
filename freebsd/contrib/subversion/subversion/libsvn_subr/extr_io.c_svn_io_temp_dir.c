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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_temp_dir ; 
 int /*<<< orphan*/  svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_dir ; 
 int /*<<< orphan*/  temp_dir_init_state ; 

svn_error_t *
svn_io_temp_dir(const char **dir,
                apr_pool_t *pool)
{
  SVN_ERR(svn_atomic__init_once(&temp_dir_init_state,
                                init_temp_dir, NULL, pool));

  *dir = apr_pstrdup(pool, temp_dir);

  return SVN_NO_ERROR;
}