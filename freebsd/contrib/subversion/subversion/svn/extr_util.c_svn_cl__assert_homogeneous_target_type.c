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
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_ERR_ILLEGAL_TARGET ; 
 TYPE_1__* svn_client__assert_homogeneous_target_type (int /*<<< orphan*/  const*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__assert_homogeneous_target_type(const apr_array_header_t *targets)
{
  svn_error_t *err;

  err = svn_client__assert_homogeneous_target_type(targets);
  if (err && err->apr_err == SVN_ERR_ILLEGAL_TARGET)
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, err, NULL);
  return err;
}