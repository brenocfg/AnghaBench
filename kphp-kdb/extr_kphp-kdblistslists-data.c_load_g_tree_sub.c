#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int N; scalar_t__ DA; scalar_t__ IA; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ listree_xglobal_t ;
struct TYPE_7__ {int /*<<< orphan*/ * g_tree_sub; } ;
struct TYPE_6__ {int* sublist_size_cum; } ;

/* Variables and functions */
 TYPE_4__* M_List ; 
 scalar_t__ M_global_id_list ; 
 TYPE_3__* M_metafile ; 
 scalar_t__ M_sublist_temp_id_by_global ; 
 int M_tot_entries ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void load_g_tree_sub (listree_xglobal_t *LX, int sublist) {
  assert (!(sublist & -8));
  LX->root = &M_List->g_tree_sub[sublist];
  if (M_metafile) {
    int curptr = M_metafile->sublist_size_cum[sublist], nxtptr = M_metafile->sublist_size_cum[sublist + 1];
    assert (curptr >= 0 && curptr <= nxtptr && nxtptr <= M_tot_entries);
    LX->N = nxtptr - curptr;
    LX->IA = M_sublist_temp_id_by_global + curptr;
    LX->DA = M_global_id_list;
  } else {
    LX->N = 0;
    LX->IA = 0;
    LX->DA = 0;
  }
}