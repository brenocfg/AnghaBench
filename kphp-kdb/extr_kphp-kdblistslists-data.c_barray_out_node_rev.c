#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 int MAX_RES ; 
 int* M_global_id_list ; 
 int /*<<< orphan*/  M_obj_id_list ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int) ; 
 int* PTR_INTS ; 
 int* R ; 
 int* R_end ; 
 int R_mode ; 
 int /*<<< orphan*/  assert (int) ; 
 int metafile_get_date (int) ; 
 int metafile_get_flags (int) ; 
 char* metafile_get_text (int,int*) ; 
 int /*<<< orphan*/  metafile_get_value (int) ; 
 int /*<<< orphan*/  store_object_id_rev (int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_value_rev (int**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int barray_out_node_rev (listree_t *LT, int temp_id) {
  int m = R_mode, *p = R_end;
  assert (R_end < R + MAX_RES);
  //assert (LT);
  if (m & 1024) {
    int text_len;
    *((char **)(p - PTR_INTS - 1)) = metafile_get_text (temp_id, &text_len);
    *--p = text_len; 
    p -= PTR_INTS;
  }
  if (m & 512) {
    store_value_rev (&p, metafile_get_value (temp_id));
  }
  if (m & 256) {
    *--p = M_global_id_list[temp_id];
  }
  if (m & 128) {
    *--p = metafile_get_date (temp_id);
  }
  if (m & 64) {
    *--p = metafile_get_flags (temp_id);
  }
  store_object_id_rev (&p, OARR_ENTRY (M_obj_id_list, temp_id));
  R_end = p;
  return 0;
}