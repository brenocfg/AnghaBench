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
typedef  scalar_t__ object_id_t ;

/* Variables and functions */
 int object_id_ints ; 
 int /*<<< orphan*/  tl_store_int (scalar_t__) ; 
 int /*<<< orphan*/  tl_store_long (scalar_t__) ; 
 int /*<<< orphan*/  tl_store_string_data (char*,int) ; 

int tl_store_object_id (object_id_t id) {
#ifdef LISTS_Z
  tl_store_string_data ((char *)id, 4 * object_id_ints);
#elif defined (LISTS64)
  tl_store_long (id);
#else
  tl_store_int (id);
#endif
  return 0;
}