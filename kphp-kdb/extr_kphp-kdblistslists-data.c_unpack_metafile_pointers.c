#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value_t ;
struct TYPE_12__ {int tot_entries; int flags; int* data; } ;
typedef  TYPE_1__ metafile_t ;
struct TYPE_13__ {int metafile_index; int /*<<< orphan*/  o_tree; } ;
typedef  TYPE_2__ list_t ;
typedef  int /*<<< orphan*/  global_id_t ;
typedef  int /*<<< orphan*/  array_object_id_t ;
struct TYPE_14__ {int N; int /*<<< orphan*/ * A; int /*<<< orphan*/ * root; } ;
struct TYPE_11__ {int list_file_offset; } ;

/* Variables and functions */
 scalar_t__ FILE_LIST_MAGIC ; 
 TYPE_10__* FLI_ENTRY_ADJUSTED (int) ; 
 int LF_BIGFLAGS ; 
 int LF_HAVE_DATES ; 
 int LF_HAVE_TEXTS ; 
 int LF_HAVE_VALUES ; 
 unsigned int MAX_METAFILE_ENTRIES ; 
 scalar_t__ MF_MAGIC (TYPE_1__*) ; 
 scalar_t__ MF_READJUST (TYPE_1__*) ; 
 TYPE_2__* M_List ; 
 int* M_dates ; 
 int* M_flags ; 
 unsigned char* M_flags_small ; 
 int /*<<< orphan*/ * M_global_id_list ; 
 TYPE_1__* M_metafile ; 
 int M_metafile_size ; 
 int /*<<< orphan*/ * M_obj_id_list ; 
 int* M_sorted_global_id_list ; 
 int* M_sublist_temp_id_by_global ; 
 int* M_sublist_temp_id_list ; 
 char* M_text_end ; 
 int M_text_max_offset ; 
 int M_text_min_offset ; 
 int* M_text_offset ; 
 char* M_text_start ; 
 int M_tot_entries ; 
 int /*<<< orphan*/ * M_values ; 
 int OBJECT_ID_INTS ; 
 TYPE_5__ OTree ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* get_metafile_ptr (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

__attribute__((used)) static void unpack_metafile_pointers (list_t *L) {
  metafile_t *M = L->metafile_index != -1 ? get_metafile_ptr (L->metafile_index) : 0;
  M_List = L;
  OTree.root = &L->o_tree;
  /*if (M == M_metafile) {
    return;
  }*/
  if (!M) {
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
    return;
  }
  assert (MF_MAGIC(M) == FILE_LIST_MAGIC);
  M_metafile = M;
  int p = L->metafile_index;
  M_metafile_size = FLI_ENTRY_ADJUSTED(p+1)->list_file_offset - FLI_ENTRY_ADJUSTED(p)->list_file_offset;
  int tot_entries = M->tot_entries, flags = M->flags, *ptr;
  vkprintf (3, "Metafile flags: %d, tot_entries = %d\n", flags, tot_entries);
  assert ((unsigned) tot_entries <= MAX_METAFILE_ENTRIES);
  OTree.N = M_tot_entries = tot_entries;
  OTree.A = M_obj_id_list = (array_object_id_t *)(ptr = M->data);
  ptr += tot_entries * OBJECT_ID_INTS;
  M_global_id_list = (global_id_t *)ptr;
  ptr += tot_entries * (sizeof (global_id_t) / sizeof (int));
  M_sorted_global_id_list = ptr;
  ptr += tot_entries;
  M_sublist_temp_id_list = ptr;
  ptr += tot_entries;
  M_sublist_temp_id_by_global = ptr;
  ptr += tot_entries;
  if (flags & LF_HAVE_VALUES) {
    M_values = (value_t *) ptr;
#ifdef VALUES64
    ptr += 2*tot_entries;
#else
    ptr += tot_entries;
#endif
  } else {
    M_values = 0;
  }
  if (flags & LF_HAVE_DATES) {
    M_dates = ptr;
    ptr += tot_entries;
  } else {
    M_dates = 0;
  }
  if (flags & LF_HAVE_TEXTS) {
    M_text_offset = ptr;
    ptr += tot_entries + 1;
  } else {
    M_text_offset = 0;
  }
  if (flags & LF_BIGFLAGS) {
    M_flags = ptr;
    M_flags_small = 0;
    M_text_start = (char *) (ptr + tot_entries);
  } else {
    M_flags_small = (unsigned char *) ptr;
    M_flags = 0;
    M_text_start = (char *) ptr + tot_entries;
  }
  M_text_end = (char *) MF_READJUST (M_metafile) + M_metafile_size;
  assert (M_text_start <= M_text_end);
  M_text_min_offset = M_text_start - (char *) MF_READJUST (M_metafile);
  M_text_max_offset = M_metafile_size;
}