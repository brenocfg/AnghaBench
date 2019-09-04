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
struct notify_item {scalar_t__ type; scalar_t__ owner; scalar_t__ place; scalar_t__ date; scalar_t__ random_tag; } ;

/* Variables and functions */

int notify_compare (const void *a, const void *b) {
  #define aa ((struct notify_item *)a)
  #define bb ((struct notify_item *)b)
  if (aa->type != bb->type) {
    return aa->type - bb->type;
  }
  if (aa->owner != bb->owner) {
    return aa->owner - bb->owner;
  }
  if (aa->place != bb->place) {
    return aa->place - bb->place;
  }
  if (aa->date != bb->date) {
    return bb->date - aa->date;
  }
  if (aa->random_tag > bb->random_tag) {
    return 1;
  }
  if (aa->random_tag < bb->random_tag) {
    return -1;
  }
  return 0;
  #undef aa
  #undef bb
}