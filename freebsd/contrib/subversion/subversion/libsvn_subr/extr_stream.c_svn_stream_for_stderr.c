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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_file_open_stderr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_stream_from_apr_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,char*) ; 

svn_error_t *
svn_stream_for_stderr(svn_stream_t **err, apr_pool_t *pool)
{
  apr_file_t *stderr_file;
  apr_status_t apr_err;

  apr_err = apr_file_open_stderr(&stderr_file, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Can't open stderr");

  /* STDERR may or may not support positioning requests, but generally
     it does not, or the behavior is implementation-specific.  Hence,
     we cannot safely advertise mark(), seek() and non-default skip()
     support. */
  *err = make_stream_from_apr_file(stderr_file, TRUE, FALSE, FALSE, pool);

  return SVN_NO_ERROR;
}