#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* is_outer_most_lock; void* is_inner_most_lock; int /*<<< orphan*/ * lock_pool; struct TYPE_6__* baton; int /*<<< orphan*/  body; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ with_lock_baton_t ;
typedef  int /*<<< orphan*/  lock_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_lock_baton (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  with_lock ; 

__attribute__((used)) static with_lock_baton_t *
chain_lock_baton(lock_id_t lock_id,
                 with_lock_baton_t *nested)
{
  /* Use the same pool for batons along the lock chain. */
  apr_pool_t *lock_pool = nested->lock_pool;
  with_lock_baton_t *result = apr_pcalloc(lock_pool, sizeof(*result));

  /* All locks along the chain operate on the same FS. */
  result->fs = nested->fs;

  /* Execution of this baton means acquiring the nested lock and its
     execution. */
  result->body = with_lock;
  result->baton = nested;

  /* Shared among all locks along the chain. */
  result->lock_pool = lock_pool;

  /* We are the new outermost lock but surely not the innermost lock. */
  result->is_inner_most_lock = FALSE;
  result->is_outer_most_lock = TRUE;
  nested->is_outer_most_lock = FALSE;

  /* Select mutex and lock file path depending on LOCK_ID.
     Also, initialize dependent members (IS_GLOBAL_LOCK only, ATM). */
  init_lock_baton(result, lock_id);

  return result;
}