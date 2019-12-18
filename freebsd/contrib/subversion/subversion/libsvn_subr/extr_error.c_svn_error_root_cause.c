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
struct TYPE_4__ {struct TYPE_4__* child; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */

svn_error_t *
svn_error_root_cause(svn_error_t *err)
{
  while (err)
    {
      /* I don't think we can change the behavior here, but the additional
         error chain doesn't define the root cause. Perhaps we should rev
         this function. */
      if (err->child /*&& err->child->apr_err != SVN_ERR_COMPOSED_ERROR*/)
        err = err->child;
      else
        break;
    }

  return err;
}