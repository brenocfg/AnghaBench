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
struct TYPE_3__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ tree23_root_t ;

/* Variables and functions */
 int /*<<< orphan*/  count_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void count (tree23_root_t *R, int *A) {
  A[0] = A[1] = A[2] = 0;
  if (!R->root) {
    return;
  }
  count_rec (R->root, R->depth, A);
}