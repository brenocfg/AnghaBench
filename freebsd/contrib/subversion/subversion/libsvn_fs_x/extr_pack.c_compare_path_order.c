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
struct TYPE_4__ {scalar_t__ revision; int /*<<< orphan*/  node_id; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ path_order_t ;

/* Variables and functions */
 int svn_fs_x__id_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_prefix_string__compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_path_order(const path_order_t * const * lhs_p,
                   const path_order_t * const * rhs_p)
{
  const path_order_t * lhs = *lhs_p;
  const path_order_t * rhs = *rhs_p;

  /* lexicographic order on path and node (i.e. latest first) */
  int diff = svn_prefix_string__compare(lhs->path, rhs->path);
  if (diff)
    return diff;

  /* reverse order on node (i.e. latest first) */
  diff = svn_fs_x__id_compare(&rhs->node_id, &lhs->node_id);
  if (diff)
    return diff;

  /* reverse order on revision (i.e. latest first) */
  if (lhs->revision != rhs->revision)
    return lhs->revision < rhs->revision ? 1 : -1;

  return 0;
}