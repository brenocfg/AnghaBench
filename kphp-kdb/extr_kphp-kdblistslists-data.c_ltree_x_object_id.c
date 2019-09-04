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
typedef  int ltree_x_t ;

/* Variables and functions */

__attribute__((used)) static inline object_id_t ltree_x_object_id (ltree_x_t ltx) {
#ifdef LISTS64
  return ltx.object_id;
#elif (defined (LISTS_Z))
  return (int *)ltx;
#else
  return (object_id_t)(ltx >> 32);
#endif
}