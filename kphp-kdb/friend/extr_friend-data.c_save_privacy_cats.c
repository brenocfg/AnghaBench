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
struct TYPE_3__ {int* cat_ver; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int* P ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void save_privacy_cats (user_t *U) {
  int *A;
  for (A = P; *A != -1; A++) {
    int x = *A;
    if ((x & 0x60000000) == 0x40000000) {
      assert (!(x & 0x3fffffe0));
      *A = (x & -0x40000000) + U->cat_ver[x & 0x1f];
    }
  }
}