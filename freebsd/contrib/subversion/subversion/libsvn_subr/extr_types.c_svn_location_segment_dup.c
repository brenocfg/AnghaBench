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
struct TYPE_5__ {scalar_t__ path; } ;
typedef  TYPE_1__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 

svn_location_segment_t *
svn_location_segment_dup(const svn_location_segment_t *segment,
                         apr_pool_t *pool)
{
  svn_location_segment_t *new_segment =
    apr_palloc(pool, sizeof(*new_segment));

  *new_segment = *segment;
  if (segment->path)
    new_segment->path = apr_pstrdup(pool, segment->path);
  return new_segment;
}