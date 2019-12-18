#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,...) ; 

const char *
svn_branch__id_nest(const char *outer_bid,
                    int outer_eid,
                    apr_pool_t *result_pool)
{
  if (!outer_bid)
    return apr_psprintf(result_pool, "B%d", outer_eid);

  return apr_psprintf(result_pool, "%s.%d", outer_bid, outer_eid);
}