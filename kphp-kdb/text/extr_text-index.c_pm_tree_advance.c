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
struct pm_tree_builder {scalar_t__ choice; } ;
typedef  int /*<<< orphan*/  pm_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  pm_tree_adva (int /*<<< orphan*/ *,struct pm_tree_builder*) ; 
 int /*<<< orphan*/  pm_tree_advb (int /*<<< orphan*/ *,struct pm_tree_builder*) ; 

__attribute__((used)) static void pm_tree_advance (pm_cell_t *A, struct pm_tree_builder *B) {
  if (B->choice) {
    pm_tree_advb (A, B);
  } else {
    pm_tree_adva (A, B);
  }
}