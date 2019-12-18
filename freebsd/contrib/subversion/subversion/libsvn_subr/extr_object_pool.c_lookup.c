#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  objects; } ;
typedef  TYPE_1__ svn_object_pool__t ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {void* object; } ;
typedef  TYPE_3__ object_ref_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_object_ref (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
lookup(void **object,
       svn_object_pool__t *object_pool,
       svn_membuf_t *key,
       apr_pool_t *result_pool)
{
  object_ref_t *object_ref
    = apr_hash_get(object_pool->objects, key->data, key->size);

  if (object_ref)
    {
      *object = object_ref->object;
      add_object_ref(object_ref, result_pool);
    }
  else
    {
      *object = NULL;
    }

  return SVN_NO_ERROR;
}