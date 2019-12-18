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

/* Variables and functions */

int
svn_fs_x__id_compare(const svn_fs_x__id_t *a,
                     const svn_fs_x__id_t *b)
{
  if (a->change_set < b->change_set)
    return -1;
  if (a->change_set > b->change_set)
    return 1;

  return a->number < b->number ? -1 : a->number == b->number ? 0 : 1;
}