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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  o_tree; } ;
typedef  TYPE_1__ list_t ;
struct TYPE_6__ {scalar_t__ A; scalar_t__ N; int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 TYPE_1__* M_List ; 
 scalar_t__ M_dates ; 
 scalar_t__ M_flags ; 
 scalar_t__ M_flags_small ; 
 scalar_t__ M_global_id_list ; 
 scalar_t__ M_metafile ; 
 scalar_t__ M_metafile_size ; 
 scalar_t__ M_obj_id_list ; 
 scalar_t__ M_sorted_global_id_list ; 
 scalar_t__ M_sublist_temp_id_by_global ; 
 scalar_t__ M_sublist_temp_id_list ; 
 scalar_t__ M_text_end ; 
 scalar_t__ M_text_max_offset ; 
 scalar_t__ M_text_min_offset ; 
 scalar_t__ M_text_offset ; 
 scalar_t__ M_text_start ; 
 scalar_t__ M_tot_entries ; 
 scalar_t__ M_values ; 
 TYPE_3__ OTree ; 

__attribute__((used)) static void unpack_metafile_pointers_short (list_t *L) {
  M_List = L;
  OTree.root = &L->o_tree;
  M_metafile = 0;
  M_metafile_size = 0;
  M_tot_entries = 0;
  M_obj_id_list = 0;
  M_global_id_list = 0;
  M_sorted_global_id_list = 0;
  M_sublist_temp_id_list = 0;
  M_sublist_temp_id_by_global = 0;
  M_values = 0;
  M_dates = 0;
  M_text_offset = 0;
  M_flags_small = 0;
  M_flags = 0;
  M_text_min_offset = 0;
  M_text_max_offset = 0;
  M_text_start = 0;
  M_text_end = 0;
  OTree.N = 0;
  OTree.A = 0;
}