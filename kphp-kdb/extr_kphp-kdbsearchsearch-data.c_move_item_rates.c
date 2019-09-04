#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_item {scalar_t__ mask; scalar_t__ rates_len; scalar_t__ rates; } ;
struct TYPE_3__ {scalar_t__ mask; scalar_t__ rates_len; scalar_t__ rates; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */

__attribute__((used)) static void move_item_rates (item_t *dst, struct index_item *src) {
  dst->rates = src->rates;
  dst->rates_len = src->rates_len;
  dst->mask = src->mask;

  src->rates = 0;
  src->rates_len = 0;
  src->mask = 0;
}