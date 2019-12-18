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

/* Variables and functions */
 int /*<<< orphan*/  PTR_INTS ; 
 int VALUE_INTS ; 
 int object_id_ints ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_long (int const) ; 
 int /*<<< orphan*/  tl_store_string (char*,int) ; 
 int /*<<< orphan*/  tl_store_string_data (void*,int) ; 

void tl_store_list_object_full (const int *R, const int *R_end, int mode, int res) {
  const int *Rptr = R;
  int i = 0;
  for (i = 0; i < res; i++) {
    if (mode & (1 << 15)) {
      tl_store_string_data ((void *)Rptr, 4 * object_id_ints);
    }
    Rptr += object_id_ints;
    if (mode & 64) { tl_store_int (*(Rptr ++)); }
    if (mode & 128) { tl_store_int (*(Rptr ++)); }
    if (mode & 256) {
      tl_store_long (*Rptr);
      Rptr ++;
    }
    if (mode & 512) {
      if (VALUE_INTS == 2) {
        tl_store_long (*(long long *)Rptr);
        Rptr += 2;
      } else {
        tl_store_long (*Rptr);
        Rptr ++;
      }
    }
    if (mode & 1024) { 
      char *text = *(char **)Rptr;
      Rptr += PTR_INTS;
      int text_len = *(Rptr ++);
      tl_store_string (text, text_len);
    }
  }
}