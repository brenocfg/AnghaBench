#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int /*<<< orphan*/ * offsets; void* last_matches; void* prefixes; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ hash_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  NO_OFFSET ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
allocate_hash_members(hash_t *hash,
                      apr_size_t size,
                      apr_pool_t *result_pool)
{
  apr_size_t i;

  hash->pool = result_pool;
  hash->size = size;

  hash->prefixes = apr_pcalloc(result_pool, size);
  hash->last_matches = apr_pcalloc(result_pool,
                                   sizeof(*hash->last_matches) * size);
  hash->offsets = apr_palloc(result_pool, sizeof(*hash->offsets) * size);

  for (i = 0; i < size; ++i)
    hash->offsets[i] = NO_OFFSET;
}