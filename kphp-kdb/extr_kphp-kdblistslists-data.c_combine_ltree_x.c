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
typedef  unsigned int var_ltree_x_t ;
typedef  scalar_t__ object_id_t ;
typedef  scalar_t__ list_id_t ;

/* Variables and functions */

__attribute__((used)) static inline void combine_ltree_x (list_id_t list_id, object_id_t object_id, var_ltree_x_t *ltx) {
#ifdef LISTS64
  ltx->list_id = list_id;
  ltx->object_id = object_id;
#elif (defined (LISTS_Z))
  memcpy (*ltx, object_id, object_id_bytes);
  memcpy (((int *)(*ltx)) + object_id_ints, list_id, list_id_bytes);
#else
  *ltx = (((long long) object_id) << 32) + (unsigned) list_id;
#endif
}