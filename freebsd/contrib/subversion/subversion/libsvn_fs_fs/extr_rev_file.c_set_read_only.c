#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  file_path; } ;
typedef  TYPE_2__ set_read_only_baton_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_io_set_file_read_only (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
set_read_only(void *baton)
{
  set_read_only_baton_t *ro_baton = baton;
  apr_status_t status = APR_SUCCESS;
  svn_error_t *err;

  err = svn_io_set_file_read_only(ro_baton->file_path, TRUE, ro_baton->pool);
  if (err)
    {
      status = err->apr_err;
      svn_error_clear(err);
    }

  return status;
}