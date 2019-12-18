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
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_baton_t {int /*<<< orphan*/  has_props; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static svn_error_t *
remove_node_props(void *node_baton)
{
  struct node_baton_t *nb = node_baton;

  /* In this case, not actually indicating that the node *has* props,
     rather that it has a property content section. */
  nb->has_props = TRUE;

  return SVN_NO_ERROR;
}