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
struct cyclic_views_entry {int dummy; } ;

/* Variables and functions */
 long CYCLIC_VIEWS_BUFFER_SIZE ; 

__attribute__((used)) static inline int subtract_CV (struct cyclic_views_entry *CV_start, struct cyclic_views_entry *CV_end) {
  long t = CV_end - CV_start;
  return t >= 0 ? t : t + CYCLIC_VIEWS_BUFFER_SIZE;
}