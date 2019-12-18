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

__attribute__((used)) static int get_cnt_type (long long cnt_id) {
  if (cnt_id >= 0) { return 0;}
  else if (cnt_id < 0 && cnt_id >= -1000000000) { return 1;}
  else if (cnt_id < -1000000000) {return 2;}
  else { return 3;}
}