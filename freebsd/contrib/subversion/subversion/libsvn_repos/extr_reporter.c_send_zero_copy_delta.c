#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ zero_copy_limit; int /*<<< orphan*/  zero_copy_succeeded; int /*<<< orphan*/  dbaton; int /*<<< orphan*/  dhandler; } ;
typedef  TYPE_1__ zero_copy_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_txdelta_send_contents (unsigned char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
send_zero_copy_delta(const unsigned char *contents,
                     apr_size_t len,
                     void *baton,
                     apr_pool_t *pool)
{
  zero_copy_baton_t *zero_copy_baton = baton;

  /* if the item is too large, the caller must revert to traditional
     streaming code. */
  if (len > zero_copy_baton->zero_copy_limit)
    {
      zero_copy_baton->zero_copy_succeeded = FALSE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_txdelta_send_contents(contents, len,
                                    zero_copy_baton->dhandler,
                                    zero_copy_baton->dbaton, pool));

  /* all fine now */
  zero_copy_baton->zero_copy_succeeded = TRUE;
  return SVN_NO_ERROR;
}