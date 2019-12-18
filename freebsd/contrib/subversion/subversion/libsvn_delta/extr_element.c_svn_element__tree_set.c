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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_element__content_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_eid__hash_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_element__tree_set(svn_element__tree_t *tree,
                      int eid,
                      const svn_element__content_t *element)
{
  svn_eid__hash_set(tree->e_map, eid, element);

  return SVN_NO_ERROR;
}