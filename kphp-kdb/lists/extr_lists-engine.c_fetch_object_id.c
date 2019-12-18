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
typedef  int /*<<< orphan*/ **** var_object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *****) ; 
 int object_id_ints ; 
 scalar_t__ tl_fetch_check (int) ; 
 int /*<<< orphan*/  tl_fetch_raw_data (int /*<<< orphan*/ *****,int) ; 

int fetch_object_id (var_object_id_t *object_id) {
  assert (object_id);
  if (tl_fetch_check (4 * object_id_ints) < 0) {
    return -1;    
  }
#ifdef LISTS_Z
  tl_fetch_raw_data (*object_id, 4 * object_id_ints);
#elif defined (LISTS64)
  tl_fetch_raw_data (object_id, 8);
#else
  tl_fetch_raw_data (object_id, 4);
#endif
  return 0;
}