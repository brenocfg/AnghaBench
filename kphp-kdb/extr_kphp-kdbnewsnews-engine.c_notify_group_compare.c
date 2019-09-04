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
struct notify_group {scalar_t__ date; scalar_t__ pos; scalar_t__ num; } ;

/* Variables and functions */

int notify_group_compare (const void *a, const void *b) {
  #define aa ((struct notify_group *)a)
  #define bb ((struct notify_group *)b)
  if (aa->date != bb->date) {
    return bb->date - aa->date;
  }
  if (aa->pos != bb->pos) {
    return aa->pos - bb->pos;
  }
  if (aa->num != bb->num) {
    return aa->num - bb->num;
  }
  return 0;
  #undef aa
  #undef bb
}