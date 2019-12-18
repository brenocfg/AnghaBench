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
struct TYPE_4__ {scalar_t__ buffered; void** hashes; } ;
typedef  TYPE_1__ svn_fnv1a_32x4__context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FNV1_BASE_32 ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_fnv1a_32x4__context_t *
svn_fnv1a_32x4__context_create(apr_pool_t *pool)
{
  svn_fnv1a_32x4__context_t *context = apr_palloc(pool, sizeof(*context));

  context->hashes[0] = FNV1_BASE_32;
  context->hashes[1] = FNV1_BASE_32;
  context->hashes[2] = FNV1_BASE_32;
  context->hashes[3] = FNV1_BASE_32;

  context->buffered = 0;

  return context;
}