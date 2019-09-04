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
struct TYPE_2__ {int /*<<< orphan*/  origin_len; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ zone_t ;

/* Variables and functions */
 int cmp_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_ptr_zone (const void *x, const void *y) {
  zone_t *a = *((zone_t **) x);
  zone_t *b = *((zone_t **) y);
  return cmp_str (a->origin, a->origin_len, b->origin, b->origin_len);
}