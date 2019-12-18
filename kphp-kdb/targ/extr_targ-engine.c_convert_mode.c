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
 int Q_order ; 

int convert_mode (int mode) {
  Q_order = 0;
  if (mode & 1) {
    Q_order = 2;
  } else if (mode & 2) {
    Q_order = 1;
  }
  if (!(mode & 4)) {
    Q_order = -Q_order;
  }
  return Q_order;
}