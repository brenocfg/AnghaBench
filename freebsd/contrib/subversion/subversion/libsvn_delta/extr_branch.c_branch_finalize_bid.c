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
 char const* svn_branch__id_nest (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__id_unnest (char const**,int*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
branch_finalize_bid(const char *bid,
                    int mapping_offset,
                    apr_pool_t *result_pool)
{
  const char *outer_bid;
  int outer_eid;

  svn_branch__id_unnest(&outer_bid, &outer_eid, bid, result_pool);

  if (outer_bid)
    {
      outer_bid = branch_finalize_bid(outer_bid, mapping_offset, result_pool);
    }

  if (outer_eid < -1)
    {
      outer_eid = mapping_offset - outer_eid;
    }

  return svn_branch__id_nest(outer_bid, outer_eid, result_pool);
}