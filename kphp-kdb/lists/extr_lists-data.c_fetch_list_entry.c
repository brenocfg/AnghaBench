#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void tree_ext_large_t ;
struct tree_payload {int flags; int date; scalar_t__ text; scalar_t__ value; scalar_t__ global_id; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_id_t ;
struct TYPE_3__ {int N; } ;

/* Variables and functions */
 scalar_t__* M_global_id_list ; 
 int NODE_RPOS (void*) ; 
 scalar_t__ NODE_TYPE (void*) ; 
 TYPE_1__ OTree ; 
 struct tree_payload* PAYLOAD (void*) ; 
 scalar_t__ TF_PLUS ; 
 int /*<<< orphan*/ * __get_list_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_text_len (scalar_t__) ; 
 char* get_text_ptr (scalar_t__) ; 
 void* listree_lookup_large (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int metafile_get_date (int) ; 
 int metafile_get_flags (int) ; 
 char* metafile_get_text (int,int*) ; 
 scalar_t__ metafile_get_value (int) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unpack_metafile_pointers (int /*<<< orphan*/ *) ; 

int fetch_list_entry (list_id_t list_id, object_id_t object_id, int result[13]) {
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }
  list_t *L = __get_list_f (list_id, 2);
  if (!L) {
    return -1;
  }

  unpack_metafile_pointers (L);

  int temp_id;
  tree_ext_large_t *T = listree_lookup_large (&OTree, object_id, &temp_id);

  if (!T) {
    return -1;
  }

  memset (result + 6, 0, 28);

  if (T != (void *) -1) {
    struct tree_payload *P = PAYLOAD (T);
    result[0] = P->flags;
    result[1] = P->date;
    *((long long *) (result + 2)) = (long long) P->global_id;
    *((long long *) (result + 4)) = (long long) P->value;

    if (P->text) {
      result[12] = get_text_len (P->text);
      *((char **) (result + 10)) = get_text_ptr (P->text);
    } else {
      assert (NODE_TYPE (T) != TF_PLUS);
      *((char **) (result + 10)) = metafile_get_text (OTree.N - NODE_RPOS (T), result + 12);
    }
  } else {
    result[0] = metafile_get_flags (temp_id);
    result[1] = metafile_get_date (temp_id);
    *((long long *) (result + 2)) = (long long) M_global_id_list[temp_id];
    *((long long *) (result + 4)) = (long long) metafile_get_value (temp_id);
    *((char **) (result + 10)) = metafile_get_text (temp_id, result + 12);
  }
  return 6;
}