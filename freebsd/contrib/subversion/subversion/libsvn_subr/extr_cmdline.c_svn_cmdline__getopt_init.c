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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_getopt_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_cmdline__getopt_init(apr_getopt_t **os,
                         int argc,
                         const char *argv[],
                         apr_pool_t *pool)
{
  apr_status_t apr_err = apr_getopt_init(os, pool, argc, argv);
  if (apr_err)
    return svn_error_wrap_apr(apr_err,
                              _("Error initializing command line arguments"));
  return SVN_NO_ERROR;
}