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
struct TYPE_4__ {scalar_t__ rev; int /*<<< orphan*/  bid; } ;
typedef  TYPE_1__ svn_branch__rev_bid_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_branch__rev_bid_equal(const svn_branch__rev_bid_t *id1,
                          const svn_branch__rev_bid_t *id2)
{
  return (id1->rev == id2->rev
          && strcmp(id1->bid, id2->bid) == 0);
}