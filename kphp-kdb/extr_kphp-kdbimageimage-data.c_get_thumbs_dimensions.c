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

__attribute__((used)) static int get_thumbs_dimensions (int orig_width, int orig_height, int desired_width, int desired_height,
                                  int *new_width, int *new_height) {
	if (orig_width == desired_width && orig_height == desired_height) {
		*new_width  = desired_width;
		*new_height = desired_height;
		return 1;
	}

  if (desired_width <= 0 || desired_height <= 0) {
    return 0;
  }

  double ratio_x = (double)desired_width / (double)orig_width;
  double ratio_y = (double)desired_height / (double)orig_height;

  if (ratio_x < ratio_y) {
    *new_width  = desired_width;
    *new_height = (0.5 - 1e-9) + ratio_x * (double)orig_height;
  } else {
    *new_height = desired_height;
    *new_width  = (0.5 - 1e-9) + ratio_y * (double)orig_width;
  }

  if (*new_width < 1) {
    *new_width = 1;
  }

  if (*new_height < 1) {
    *new_height = 1;
  }
  return 1;
}