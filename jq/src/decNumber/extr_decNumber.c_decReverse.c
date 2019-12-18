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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */

__attribute__((used)) static void decReverse(Unit *ulo, Unit *uhi) {
  Unit temp;
  for (; ulo<uhi; ulo++, uhi--) {
    temp=*ulo;
    *ulo=*uhi;
    *uhi=temp;
    }
  return;
  }