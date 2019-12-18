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
struct item {scalar_t__ mask; scalar_t__ rates_len; scalar_t__ rates; } ;
struct index_item {scalar_t__ mask; scalar_t__ rates_len; scalar_t__ rates; } ;

/* Variables and functions */

__attribute__((used)) static void move_item_rates (struct item *dst, struct index_item *src) {
  dst->rates = src->rates;
  dst->rates_len = src->rates_len;
  dst->mask = src->mask;

  src->rates = 0;
  src->rates_len = 0;
  src->mask = 0;
}