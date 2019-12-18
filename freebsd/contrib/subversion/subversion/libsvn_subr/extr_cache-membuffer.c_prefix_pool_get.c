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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ prefix_pool_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  prefix_pool_get_internal (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

__attribute__((used)) static svn_error_t *
prefix_pool_get(apr_uint32_t *prefix_idx,
                prefix_pool_t *prefix_pool,
                const char *prefix)
{
  SVN_MUTEX__WITH_LOCK(prefix_pool->mutex,
                       prefix_pool_get_internal(prefix_idx, prefix_pool,
                                                prefix));

  return SVN_NO_ERROR;
}