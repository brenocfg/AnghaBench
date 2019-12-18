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
struct TYPE_6__ {TYPE_1__* object_pool; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_2__ object_ref_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  unused_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_pre_cleanup_register (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_ref_cleanup ; 
 int /*<<< orphan*/  svn_atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_object_ref(object_ref_t *object_ref,
              apr_pool_t *pool)
{
  /* Update ref counter.
     Note that this is racy with object_ref_cleanup; see comment there. */
  if (svn_atomic_inc(&object_ref->ref_count) == 0)
    svn_atomic_dec(&object_ref->object_pool->unused_count);

  /* Make sure the reference gets released automatically.
     Since POOL might be a parent pool of OBJECT_REF->OBJECT_POOL,
     to the reference counting update before destroing any of the
     pool hierarchy. */
  apr_pool_pre_cleanup_register(pool, object_ref, object_ref_cleanup);
}