#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_id_t ;
struct TYPE_7__ {int (* compare ) (TYPE_2__ const*,TYPE_2__ const*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__ const*,TYPE_2__ const*) ; 
#define  svn_fs_node_common_ancestor 129 
#define  svn_fs_node_unchanged 128 

int
svn_fs_compare_ids(const svn_fs_id_t *a, const svn_fs_id_t *b)
{
  switch (a->vtable->compare(a, b))
    {
    case svn_fs_node_unchanged:
      return 0;
    case svn_fs_node_common_ancestor:
      return 1;
    default:
      return -1;
    }
}