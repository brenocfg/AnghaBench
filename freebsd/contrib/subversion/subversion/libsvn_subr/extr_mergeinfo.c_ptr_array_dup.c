#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {size_t nelts; scalar_t__ elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 TYPE_1__* apr_array_make (int /*<<< orphan*/ *,size_t,int) ; 
 char* apr_palloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static apr_array_header_t *
ptr_array_dup(const apr_array_header_t *array,
              size_t object_size,
              apr_pool_t *pool)
{
  apr_array_header_t *new_array = apr_array_make(pool, array->nelts,
                                                 sizeof(void *));

  /* allocate target range buffer with a single operation */
  char *copy = apr_palloc(pool, object_size * array->nelts);

  /* for efficiency, directly address source and target reference buffers */
  void **source = (void **)(array->elts);
  void **target = (void **)(new_array->elts);
  int i;

  /* copy ranges iteratively and link them into the target range list */
  for (i = 0; i < array->nelts; i++)
    {
      target[i] = &copy[i * object_size];
      memcpy(target[i], source[i], object_size);
    }
  new_array->nelts = array->nelts;

  return new_array;
}