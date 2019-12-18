#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ segment_count; } ;
typedef  TYPE_1__ svn_membuffer_t ;
struct TYPE_10__ {TYPE_1__* membuffer; } ;
typedef  TYPE_2__ svn_membuffer_cache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ svn_cache__info_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  WITH_READ_LOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_prefix_key (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_membuffer_get_segment_info (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
svn_membuffer_cache_get_info(void *cache_void,
                             svn_cache__info_t *info,
                             svn_boolean_t reset,
                             apr_pool_t *result_pool)
{
  svn_membuffer_cache_t *cache = cache_void;
  apr_uint32_t i;

  /* cache front-end specific data */

  info->id = apr_pstrdup(result_pool, get_prefix_key(cache));

  /* collect info from shared cache back-end */

  for (i = 0; i < cache->membuffer->segment_count; ++i)
    {
      svn_membuffer_t *segment = cache->membuffer + i;
      WITH_READ_LOCK(segment,
                     svn_membuffer_get_segment_info(segment, info, FALSE));
    }

  return SVN_NO_ERROR;
}