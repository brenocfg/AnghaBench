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
typedef  int /*<<< orphan*/  var_object_id_t ;
typedef  int /*<<< orphan*/  array_object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  OARR_ENTRY_ADJ (int /*<<< orphan*/ *,int) ; 
 scalar_t__ __have_weights ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_id_bytes_adjusted ; 
 int object_id_ints_adjusted ; 
 scalar_t__ object_id_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isort (array_object_id_t *A, int b) {
  int i, j;
  var_object_id_t h, t;
  if (b <= 0) { return; }
  i = 0;  j = b;  
  #ifdef LISTS_Z
  memcpy (h, OARR_ENTRY_ADJ (A, b >> 1), object_id_bytes_adjusted);
  #else
  h = OARR_ENTRY_ADJ (A, b >> 1);
  #endif
  do {
    while (object_id_less (OARR_ENTRY_ADJ (A, i), h)) { i++; }
    while (object_id_less (h, OARR_ENTRY_ADJ (A, j))) { j--; }
    if (i <= j) {
      #ifdef LISTS_Z
      memcpy (t, OARR_ENTRY_ADJ (A, i), object_id_bytes_adjusted);
      memcpy (OARR_ENTRY_ADJ (A, i), OARR_ENTRY_ADJ (A, j), object_id_bytes_adjusted);
      memcpy (OARR_ENTRY_ADJ (A, j), t, object_id_bytes_adjusted);
      #else
      if (__have_weights) {
        t = A[2*i];  A[2*i] = A[2*j];  A[2*j] = t;
        t = A[2*i+1];  A[2*i+1] = A[2*j+1];  A[2*j] = t;
      } else {
        t = A[i];  A[i] = A[j];  A[j] = t;
      }
      #endif
      i++; 
      j--;
    }
  } while (i <= j);
  isort (A, j);
  #ifdef LISTS_Z
  isort (A+i*object_id_ints_adjusted, b-i);
  #else
  isort (A+i, b-i);
  #endif
}