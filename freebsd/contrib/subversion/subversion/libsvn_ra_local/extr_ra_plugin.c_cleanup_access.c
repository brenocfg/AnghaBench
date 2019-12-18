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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_fs_set_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
cleanup_access(void *data)
{
  svn_error_t *serr;
  svn_fs_t *fs = data;

  serr = svn_fs_set_access(fs, NULL);

  if (serr)
    {
      apr_status_t apr_err = serr->apr_err;
      svn_error_clear(serr);
      return apr_err;
    }

  return APR_SUCCESS;
}