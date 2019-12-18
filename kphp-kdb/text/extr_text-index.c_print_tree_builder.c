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
struct pm_tree_builder {int choice; size_t* next; int /*<<< orphan*/ * freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ pm_cell_t ;

/* Variables and functions */
 struct pm_tree_builder* PB ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline void print_tree_builder (pm_cell_t *A, struct pm_tree_builder *B) {
  fprintf (stderr, "TB[%d]: %d {%d, %lld} {%d: (%d, %d), %lld}\n", (int) (B - PB), B->choice, B->next[0], B->freq[0], B->next[1], A[B->next[1]].left, A[B->next[1]].right, B->freq[1]);
}