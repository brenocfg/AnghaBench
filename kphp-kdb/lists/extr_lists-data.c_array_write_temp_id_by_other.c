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
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_3__ {int /*<<< orphan*/ * IA; } ;
typedef  TYPE_1__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_obj_id_list ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_temp_id_by_object_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int array_write_temp_id_by_other (listree_t *LT, int temp_id) {
  object_id_t object_id = OARR_ENTRY (M_obj_id_list, LT->IA[temp_id]);
  return write_temp_id_by_object_id (object_id);
}