#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* o_tree; } ;
typedef  TYPE_2__ list_t ;
typedef  int /*<<< orphan*/  list_id_t ;
struct TYPE_5__ {int delta; } ;

/* Variables and functions */
 int M_tot_entries ; 
 int SUBCATS ; 
 TYPE_2__* __get_list_f (int /*<<< orphan*/ ,int) ; 
 int metafile_get_sublist_size (int) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unpack_metafile_pointers (TYPE_2__*) ; 

int fetch_list_counters (list_id_t list_id, int result[SUBCATS+1]) {
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }
  int i;
  list_t *L = __get_list_f (list_id, 2);
  if (!L) {
    return -1;
  }
  unpack_metafile_pointers (L);

  result[0] = M_tot_entries + L->o_tree->delta;
  for (i = 0; i < 8; i++) {
    result[i + 1] = metafile_get_sublist_size (i);
  }

  return SUBCATS+1;
}