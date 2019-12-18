#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t* IA; int /*<<< orphan*/ * DA; } ;
typedef  TYPE_1__ listree_xglobal_t ;
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_obj_id_list ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,size_t) ; 
 int b_out_g_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int darray_out_node_rev (listree_t *LI, int temp_id) {
  listree_xglobal_t *LX = (listree_xglobal_t *)LI;
  return b_out_g_rev (OARR_ENTRY (M_obj_id_list, LX->IA[temp_id]), LX->DA[LX->IA[temp_id]]);
}