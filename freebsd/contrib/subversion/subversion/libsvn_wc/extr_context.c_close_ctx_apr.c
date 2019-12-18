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
struct TYPE_5__ {int /*<<< orphan*/  db; scalar_t__ close_db_on_destroy; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_6__ {int apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int apr_status_t ;

/* Variables and functions */
 int APR_SUCCESS ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_wc__db_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
close_ctx_apr(void *data)
{
  svn_wc_context_t *ctx = data;

  if (ctx->close_db_on_destroy)
    {
      svn_error_t *err = svn_wc__db_close(ctx->db);
      if (err)
        {
          int result = err->apr_err;
          svn_error_clear(err);
          return result;
        }
    }

  return APR_SUCCESS;
}