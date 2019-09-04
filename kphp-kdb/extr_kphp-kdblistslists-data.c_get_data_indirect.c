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
struct TYPE_3__ {int /*<<< orphan*/ * IA; int /*<<< orphan*/  DA; } ;
typedef  TYPE_1__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline object_id_t get_data_indirect (listree_t *LI, int index) {
  return OARR_ENTRY (LI->DA, LI->IA[index]);
}