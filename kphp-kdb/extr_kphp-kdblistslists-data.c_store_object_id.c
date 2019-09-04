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
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int OBJECT_ID_INTS ; 

__attribute__((used)) static inline void store_object_id (int **P, object_id_t object_id) {
  //*((*(object_id_t **)P)++) = object_id;
  //GNU C MUST DIE
  int *PVal = *P;
  #ifdef LISTS_Z
  memcpy (PVal, object_id, object_id_bytes);
  #else
  *(object_id_t *)PVal = object_id;
  #endif
  *P = PVal + OBJECT_ID_INTS;
}