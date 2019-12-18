#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct TYPE_4__ {int /*<<< orphan*/  wcroot_abspath; TYPE_1__* ctx; } ;
typedef  TYPE_2__ callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_pristine_contents_by_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_wc_contents(void *baton,
                svn_stream_t **contents,
                const svn_checksum_t *checksum,
                apr_pool_t *pool)
{
  callback_baton_t *cb = baton;

  if (! cb->wcroot_abspath)
    {
      *contents = NULL;
      return SVN_NO_ERROR;
    }

  return svn_error_trace(
             svn_wc__get_pristine_contents_by_checksum(contents,
                                                       cb->ctx->wc_ctx,
                                                       cb->wcroot_abspath,
                                                       checksum,
                                                       pool, pool));
}