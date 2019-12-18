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
typedef  int svn_boolean_t ;
struct TYPE_7__ {scalar_t__ (* compare ) (TYPE_2__ const*,TYPE_2__ const*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__ const*,TYPE_2__ const*) ; 
 scalar_t__ svn_fs_node_unrelated ; 

svn_boolean_t
svn_fs_check_related(const svn_fs_id_t *a, const svn_fs_id_t *b)
{
  return (a->vtable->compare(a, b) != svn_fs_node_unrelated);
}