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
struct index_item {scalar_t__ item_id; scalar_t__ mask; scalar_t__ rates_len; scalar_t__ extra; scalar_t__* rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bread (scalar_t__*,int) ; 
 scalar_t__ popcount_short (scalar_t__) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 
 scalar_t__* zmalloc (int) ; 

int load_item (struct index_item *C) {
  vkprintf (5, "loading item...");
  bread (&C->item_id, 8);
  /* read mask, rates_len, extra */
  bread (&C->mask, 2);
  bread (&C->rates_len, 1);
  bread (&C->extra, 1);
  int sz = ((int) C->rates_len) * sizeof (int);
  C->rates = zmalloc (sz);
  bread (C->rates, sz);
  assert (popcount_short (C->mask) == C->rates_len);
  return sz + 12;
}