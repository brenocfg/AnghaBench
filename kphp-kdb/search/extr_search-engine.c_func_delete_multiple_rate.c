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
struct hashset_int {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashset_int_insert (struct hashset_int*,int) ; 

__attribute__((used)) static void func_delete_multiple_rate (void *ctx, int i) {
  struct hashset_int *H = (struct hashset_int *) ctx;
  if (i) {
    hashset_int_insert (H, i);
  }
}