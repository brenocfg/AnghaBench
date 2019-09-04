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
typedef  int /*<<< orphan*/  listree_t ;
typedef  int /*<<< orphan*/  listree_direct_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_data_direct (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline object_id_t get_data_direct_compatible (listree_t *LT, int index) {
  return get_data_direct ((listree_direct_t *) LT, index);
}