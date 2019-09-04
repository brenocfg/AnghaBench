#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; scalar_t__ owner; scalar_t__ place; } ;
typedef  TYPE_1__ recommend_place_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_recommend_item (const void *a, const void *b) {
  const recommend_place_t *aa = *(const recommend_place_t **) a;
  const recommend_place_t *bb = *(const recommend_place_t **) b;
  if (aa->type < bb->type) {
    return -1;
  }
  if (aa->type > bb->type) {
    return 1;
  }
  if (aa->owner < bb->owner) {
    return -1;
  }
  if (aa->owner > bb->owner) {
    return 1;
  }
  if (aa->place < bb->place) {
    return -1;
  }
  if (aa->place > bb->place) {
    return 1;
  }
  return 0;
}