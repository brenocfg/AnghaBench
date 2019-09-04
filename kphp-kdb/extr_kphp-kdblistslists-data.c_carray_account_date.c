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
struct TYPE_3__ {int /*<<< orphan*/ * IA; int /*<<< orphan*/  DA; } ;
typedef  TYPE_1__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int b_account_date (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int carray_account_date (listree_t *LI, int temp_id) {
  return b_account_date (OARR_ENTRY (LI->DA, LI->IA[temp_id]));
}