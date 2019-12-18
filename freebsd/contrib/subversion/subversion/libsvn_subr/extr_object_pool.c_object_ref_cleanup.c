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
struct TYPE_3__ {int /*<<< orphan*/  unused_count; } ;
typedef  TYPE_1__ svn_object_pool__t ;
struct TYPE_4__ {int /*<<< orphan*/  ref_count; TYPE_1__* object_pool; } ;
typedef  TYPE_2__ object_ref_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ svn_atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
object_ref_cleanup(void *baton)
{
  object_ref_t *object = baton;
  svn_object_pool__t *object_pool = object->object_pool;

  /* If we released the last reference to object, there is one more
     unused entry.

     Note that unused_count does not need to be always exact but only
     needs to become exact *eventually* (we use it to check whether we
     should remove unused objects every now and then).  I.e. it must
     never drift off / get stuck but always reflect the true value once
     all threads left the racy sections.
   */
  if (svn_atomic_dec(&object->ref_count) == 0)
    svn_atomic_inc(&object_pool->unused_count);

  return APR_SUCCESS;
}