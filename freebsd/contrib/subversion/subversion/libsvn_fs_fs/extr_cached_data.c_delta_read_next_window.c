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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct delta_read_baton {TYPE_1__* rs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {scalar_t__ current; scalar_t__ size; int /*<<< orphan*/  chunk_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_delta_window (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delta_read_next_window(svn_txdelta_window_t **window, void *baton,
                       apr_pool_t *pool)
{
  struct delta_read_baton *drb = baton;
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  *window = NULL;
  if (drb->rs->current < drb->rs->size)
    {
      SVN_ERR(read_delta_window(window, drb->rs->chunk_index, drb->rs, pool,
                                scratch_pool));
      drb->rs->chunk_index++;
    }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}