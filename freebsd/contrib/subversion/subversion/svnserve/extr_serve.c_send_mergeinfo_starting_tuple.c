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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ starting_tuple_sent; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ mergeinfo_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static svn_error_t *
send_mergeinfo_starting_tuple(mergeinfo_receiver_baton_t *baton,
                              apr_pool_t *scratch_pool)
{
  if (baton->starting_tuple_sent)
    return SVN_NO_ERROR;

  SVN_ERR(svn_ra_svn__write_tuple(baton->conn, scratch_pool,
                                  "w((!", "success"));
  baton->starting_tuple_sent = TRUE;

  return SVN_NO_ERROR;
}