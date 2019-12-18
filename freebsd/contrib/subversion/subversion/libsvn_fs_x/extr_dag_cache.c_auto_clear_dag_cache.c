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
struct TYPE_3__ {scalar_t__ insertions; int /*<<< orphan*/  buckets; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_fs_x__dag_cache_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 scalar_t__ BUCKET_COUNT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
auto_clear_dag_cache(svn_fs_x__dag_cache_t* cache)
{
  if (cache->insertions <= BUCKET_COUNT)
    return FALSE;

  svn_pool_clear(cache->pool);

  memset(cache->buckets, 0, sizeof(cache->buckets));
  cache->insertions = 0;

  return TRUE;
}