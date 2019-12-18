#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** o_tree_sub; } ;
struct TYPE_5__ {int* sublist_size_cum; } ;
struct TYPE_4__ {scalar_t__ delta; } ;

/* Variables and functions */
 TYPE_3__* M_List ; 
 TYPE_2__* M_metafile ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) inline static int metafile_get_sublist_size (int sublist) {
  assert (!(sublist & -8));
  int x = M_metafile ? M_metafile->sublist_size_cum[sublist+1] - M_metafile->sublist_size_cum[sublist] : 0;
  x += M_List->o_tree_sub[sublist]->delta;
  return x;
}