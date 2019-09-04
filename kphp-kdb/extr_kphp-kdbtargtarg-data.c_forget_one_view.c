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
 scalar_t__ CV_r ; 
 scalar_t__ CViews ; 
 scalar_t__ CYCLIC_VIEWS_BUFFER_SIZE ; 
 int /*<<< orphan*/  forget_view (scalar_t__) ; 

void forget_one_view (void) {
  forget_view (CV_r);
  if (++CV_r == CViews + CYCLIC_VIEWS_BUFFER_SIZE) {
    CV_r = CViews;
  }
}