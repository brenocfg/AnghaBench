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
typedef  int /*<<< orphan*/  svn_repos_node_t ;
struct edit_baton {int /*<<< orphan*/ * node; } ;

/* Variables and functions */

svn_repos_node_t *
svn_repos_node_from_baton(void *edit_baton)
{
  struct edit_baton *eb = edit_baton;
  return eb->node;
}