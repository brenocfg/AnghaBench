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
typedef  scalar_t__ vptr ;
typedef  int /*<<< orphan*/  restore_list ;

/* Variables and functions */
 int /*<<< orphan*/  restore_list_free_rec (int /*<<< orphan*/ *) ; 

void free_restore_list (int *i, vptr *v) {
  restore_list *list = (restore_list *)*v;
  restore_list_free_rec (list);
}