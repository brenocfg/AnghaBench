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

/* Variables and functions */

int new_type (int x) {
  switch (x) {
    case 1: return 21;
    case 2: return 22;
    case 3: return 20;
    case 4: return 23;
    case 5: return 24;
    default:
      break;
  }
  return 33;

}