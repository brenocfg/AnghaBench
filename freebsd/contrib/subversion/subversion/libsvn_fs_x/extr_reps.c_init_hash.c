#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int shift; scalar_t__ used; } ;
typedef  TYPE_1__ hash_t ;
typedef  int /*<<< orphan*/  hash_key_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_hash_members (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_hash(hash_t *hash,
          apr_size_t twoPower,
          apr_pool_t *result_pool)
{
  hash->used = 0;
  hash->shift = sizeof(hash_key_t) * 8 - twoPower;

  allocate_hash_members(hash, 1 << twoPower, result_pool);
}