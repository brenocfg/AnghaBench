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
 int* sort_rec (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int *sort (tree23_root_t *R, int *st) {
  if (!R->root) {
    return st;
  }
  return sort_rec (R->root, st, R->depth);
}