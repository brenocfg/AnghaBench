#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_RESERVED_FILENAME_SPECIFIED ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_opt_args_to_target_array3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt_args_to_target_array2(apr_array_header_t **targets_p,
                              apr_getopt_t *os,
                              const apr_array_header_t *known_targets,
                              apr_pool_t *pool)
{
  svn_error_t *err = svn_opt_args_to_target_array3(targets_p, os,
                                                   known_targets, pool);

  if (err && err->apr_err == SVN_ERR_RESERVED_FILENAME_SPECIFIED)
    {
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }

  return err;
}