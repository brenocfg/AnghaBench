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
struct TYPE_3__ {scalar_t__ depth; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ tree23_root_t ;

/* Variables and functions */
 scalar_t__ check_rec (int /*<<< orphan*/ ,int,int,scalar_t__) ; 

__attribute__((used)) static int check (tree23_root_t *R) {
  if (!R->root) {
    if (R->depth) {
      return -1;
    }
    return 0;
  }
  if (R->depth < 0) {
    return -1;
  }
  return check_rec (R->root, -1 << 31, ~(-1 << 31), R->depth) ? R->depth : -1;
}