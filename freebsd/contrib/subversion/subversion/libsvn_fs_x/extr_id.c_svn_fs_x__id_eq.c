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
struct TYPE_4__ {scalar_t__ change_set; scalar_t__ number; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */

svn_boolean_t
svn_fs_x__id_eq(const svn_fs_x__id_t *lhs,
                const svn_fs_x__id_t *rhs)
{
  return lhs->change_set == rhs->change_set && lhs->number == rhs->number;
}