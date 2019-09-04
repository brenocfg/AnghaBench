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
 int /*<<< orphan*/  CV_r ; 
 int /*<<< orphan*/  CV_w ; 
 int subtract_CV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int get_recent_views_num (void) {
  return subtract_CV (CV_r, CV_w);
}