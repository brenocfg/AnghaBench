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
struct TYPE_5__ {int /*<<< orphan*/  base_rev; int /*<<< orphan*/  repos; } ;
typedef  TYPE_1__ svn_branch__txn_t ;

/* Variables and functions */
 TYPE_1__* svn_branch__repos_get_revision (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_branch__txn_t *
svn_branch__repos_get_base_revision_root(svn_branch__txn_t *rev_root)
{
  return svn_branch__repos_get_revision(rev_root->repos, rev_root->base_rev);
}