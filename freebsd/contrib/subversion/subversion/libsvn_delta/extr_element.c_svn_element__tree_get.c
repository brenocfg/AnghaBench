#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_element__content_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_eid__hash_get (int /*<<< orphan*/ ,int) ; 

svn_element__content_t *
svn_element__tree_get(const svn_element__tree_t *tree,
                      int eid)
{
  return svn_eid__hash_get(tree->e_map, eid);
}