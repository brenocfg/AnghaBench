#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ max_in; scalar_t__ current_in; scalar_t__ max_out; scalar_t__ current_out; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_SVN_REQUEST_SIZE ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_RESPONSE_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
check_io_limits(svn_ra_svn_conn_t *conn)
{
  if (conn->max_in && (conn->current_in > conn->max_in))
    return svn_error_create(SVN_ERR_RA_SVN_REQUEST_SIZE, NULL,
                            "The client request size exceeds the "
                            "configured limit");

  if (conn->max_out && (conn->current_out > conn->max_out))
    return svn_error_create(SVN_ERR_RA_SVN_RESPONSE_SIZE, NULL,
                            "The server response size exceeds the "
                            "configured limit");

  return SVN_NO_ERROR;
}