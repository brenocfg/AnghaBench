#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
struct TYPE_8__ {TYPE_1__* data_rep; } ;
typedef  TYPE_2__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  rep_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  md5_digest; int /*<<< orphan*/ * rs; } ;
typedef  TYPE_3__ delta_read_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  md5_digest; } ;

/* Variables and functions */
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  delta_read_md5_digest ; 
 int /*<<< orphan*/  delta_read_next_window ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_txdelta_stream_create (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_txdelta_stream_t *
get_storaged_delta_stream(rep_state_t *rep_state,
                          svn_fs_x__noderev_t *target,
                          apr_pool_t *result_pool)
{
  /* Create the delta read baton. */
  delta_read_baton_t *drb = apr_pcalloc(result_pool, sizeof(*drb));
  drb->rs = rep_state;
  memcpy(drb->md5_digest, target->data_rep->md5_digest,
         sizeof(drb->md5_digest));
  return svn_txdelta_stream_create(drb, delta_read_next_window,
                                   delta_read_md5_digest, result_pool);
}