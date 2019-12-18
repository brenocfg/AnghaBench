#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  unused_count; int /*<<< orphan*/  object_count; int /*<<< orphan*/  objects; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ svn_object_pool__t ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pool; TYPE_1__ key; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_3__ object_ref_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_unused_objects(svn_object_pool__t *object_pool)
{
  apr_pool_t *subpool = svn_pool_create(object_pool->pool);

  /* process all hash buckets */
  apr_hash_index_t *hi;
  for (hi = apr_hash_first(subpool, object_pool->objects);
       hi != NULL;
       hi = apr_hash_next(hi))
    {
      object_ref_t *object_ref = apr_hash_this_val(hi);

      /* note that we won't hand out new references while access
         to the hash is serialized */
      if (svn_atomic_read(&object_ref->ref_count) == 0)
        {
          apr_hash_set(object_pool->objects, object_ref->key.data,
                       object_ref->key.size, NULL);
          svn_atomic_dec(&object_pool->object_count);
          svn_atomic_dec(&object_pool->unused_count);

          svn_pool_destroy(object_ref->pool);
        }
    }

  svn_pool_destroy(subpool);
}