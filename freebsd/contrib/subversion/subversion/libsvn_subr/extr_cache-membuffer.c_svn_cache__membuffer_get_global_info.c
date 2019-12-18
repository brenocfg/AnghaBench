#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ segment_count; } ;
typedef  TYPE_1__ svn_membuffer_t ;
struct TYPE_9__ {char* id; } ;
typedef  TYPE_2__ svn_cache__info_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* svn_cache__get_global_membuffer_cache () ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_membuffer_get_global_segment_info (TYPE_1__*,TYPE_2__*) ; 

svn_cache__info_t *
svn_cache__membuffer_get_global_info(apr_pool_t *pool)
{
  apr_uint32_t i;

  svn_membuffer_t *membuffer = svn_cache__get_global_membuffer_cache();
  svn_cache__info_t *info = apr_pcalloc(pool, sizeof(*info));

  /* cache front-end specific data */

  info->id = "membuffer globals";

  /* collect info from shared cache back-end */

  for (i = 0; i < membuffer->segment_count; ++i)
    svn_error_clear(svn_membuffer_get_global_segment_info(membuffer + i,
                                                          info));

  return info;
}