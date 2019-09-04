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
struct TYPE_2__ {scalar_t__ volume_id; } ;
typedef  TYPE_1__ volume_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_volumes (const void *x, const void *y) {
  const volume_t *a = *(const volume_t **) x;
  const volume_t *b = *(const volume_t **) y;
  if (a->volume_id < b->volume_id) {
    return -1;
  }
  if (a->volume_id > b->volume_id) {
    return 1;
  }
  return 0;
}