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
struct tl_list_entry_get {int mode; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int* R ; 
 int TL_MAYBE_FALSE ; 
 int TL_MAYBE_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int fetch_list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_long (long long) ; 
 int /*<<< orphan*/  tl_store_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_string (char*,int) ; 

int tl_do_list_entry_get (struct tl_act_extra *extra) {
  struct tl_list_entry_get *e = (void *)(extra->extra);
  int res = fetch_list_entry (e->list_id, e->object_id, R);
  if (res == -2) { return -2; }
  if (res < 0) {    
    tl_store_int (TL_MAYBE_FALSE);
    return 0;
  }
  assert (res == 6);
  int text_len = R[12];

  tl_store_int (TL_MAYBE_TRUE);
  //tl_store_int (text_len > 0 ? 31 << 6 : 15 << 6);

  if (e->mode & (1 << 15)) {
    tl_store_object_id (e->object_id);
  }
  if (e->mode & (1 << 6)) {
    tl_store_int (R[0]);
  }
  if (e->mode & (1 << 7)) {
    tl_store_int (R[1]);
  }
  if (e->mode & (1 << 8)) { 
    tl_store_long (*(long long *)(R + 2));
  }
  if (e->mode & (1 << 9)) {
    tl_store_long (*(long long *)(R + 4));
  }
  if (e->mode & (1 << 10)) {
    char **text = (char **)(R + 10);
    tl_store_string (text ? *text : 0, text_len);
  }
  return 0;
}