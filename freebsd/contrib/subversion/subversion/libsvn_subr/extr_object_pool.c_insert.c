#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  objects; int /*<<< orphan*/  unused_count; int /*<<< orphan*/  object_count; } ;
typedef  TYPE_1__ svn_object_pool__t ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {void* object; TYPE_1__* object_pool; TYPE_4__ key; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ object_ref_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_object_ref (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int apr_hash_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_unused_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_atomic_inc (int /*<<< orphan*/ *) ; 
 int svn_atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_membuf__create (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
insert(void **object,
       svn_object_pool__t *object_pool,
       const svn_membuf_t *key,
       void *item,
       apr_pool_t *item_pool,
       apr_pool_t *result_pool)
{
  object_ref_t *object_ref
    = apr_hash_get(object_pool->objects, key->data, key->size);
  if (object_ref)
    {
      /* Destroy the new one and return a reference to the existing one
       * because the existing one may already have references on it.
       */
      svn_pool_destroy(item_pool);
    }
  else
    {
      /* add new index entry */
      object_ref = apr_pcalloc(item_pool, sizeof(*object_ref));
      object_ref->object_pool = object_pool;
      object_ref->object = item;
      object_ref->pool = item_pool;

      svn_membuf__create(&object_ref->key, key->size, item_pool);
      object_ref->key.size = key->size;
      memcpy(object_ref->key.data, key->data, key->size);

      apr_hash_set(object_pool->objects, object_ref->key.data,
                   object_ref->key.size, object_ref);
      svn_atomic_inc(&object_pool->object_count);

      /* the new entry is *not* in use yet.
       * add_object_ref will update counters again.
       */
      svn_atomic_inc(&object_ref->object_pool->unused_count);
    }

  /* return a reference to the object we just added */
  *object = object_ref->object;
  add_object_ref(object_ref, result_pool);

  /* limit memory usage */
  if (svn_atomic_read(&object_pool->unused_count) * 2
      > apr_hash_count(object_pool->objects) + 2)
    remove_unused_objects(object_pool);

  return SVN_NO_ERROR;
}