#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * root; int /*<<< orphan*/  DA; int /*<<< orphan*/  IA; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ listree_xglobal_t ;
struct TYPE_5__ {int /*<<< orphan*/  g_tree; } ;

/* Variables and functions */
 TYPE_3__* M_List ; 
 int /*<<< orphan*/  M_global_id_list ; 
 int /*<<< orphan*/  M_sorted_global_id_list ; 
 int /*<<< orphan*/  M_tot_entries ; 

__attribute__((used)) static inline void load_g_tree (listree_xglobal_t *LX) {
  LX->N = M_tot_entries;
  LX->IA = M_sorted_global_id_list;
  LX->DA = M_global_id_list;
  LX->root = &M_List->g_tree;
}