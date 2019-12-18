#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* largest_changes; } ;
typedef  TYPE_2__ svn_fs_fs__stats_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int count; int min_size; TYPE_1__** changes; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  revision; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
initialize_largest_changes(svn_fs_fs__stats_t *stats,
                           apr_size_t count,
                           apr_pool_t *result_pool)
{
  apr_size_t i;

  stats->largest_changes = apr_pcalloc(result_pool,
                                       sizeof(*stats->largest_changes));
  stats->largest_changes->count = count;
  stats->largest_changes->min_size = 1;
  stats->largest_changes->changes
    = apr_palloc(result_pool, count * sizeof(*stats->largest_changes->changes));

  /* allocate *all* entries before the path stringbufs.  This increases
   * cache locality and enhances performance significantly. */
  for (i = 0; i < count; ++i)
    stats->largest_changes->changes[i]
      = apr_palloc(result_pool, sizeof(**stats->largest_changes->changes));

  /* now initialize them and allocate the stringbufs */
  for (i = 0; i < count; ++i)
    {
      stats->largest_changes->changes[i]->size = 0;
      stats->largest_changes->changes[i]->revision = SVN_INVALID_REVNUM;
      stats->largest_changes->changes[i]->path
        = svn_stringbuf_create_ensure(1024, result_pool);
    }
}