#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ apr_err; struct TYPE_5__* child; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 TYPE_1__* SVN_NO_ERROR ; 

svn_error_t *
svn_error_find_cause(svn_error_t *err, apr_status_t apr_err)
{
  svn_error_t *child;

  for (child = err; child; child = child->child)
    if (child->apr_err == apr_err)
      return child;

  return SVN_NO_ERROR;
}