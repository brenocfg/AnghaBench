#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* fs; } ;
typedef  TYPE_2__ svn_fs_x__id_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_cleanup ; 

__attribute__((used)) static apr_status_t
owner_cleanup(void *baton)
{
  svn_fs_x__id_context_t *context = baton;

  /* Everything in CONTEXT gets cleaned up automatically.
     However, we must prevent notifications from other pools. */
  apr_pool_cleanup_kill(context->fs->pool, context, fs_cleanup);

  return  APR_SUCCESS;
}