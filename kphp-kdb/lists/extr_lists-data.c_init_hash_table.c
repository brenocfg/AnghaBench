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
 int LISTS_PRIME ; 
 int /*<<< orphan*/  List ; 
 int am_choose_hash_prime (int) ; 
 int lists_prime ; 
 int /*<<< orphan*/  malloc (int) ; 
 double max_lists ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void init_hash_table (int x) {
  x = (int)x * 1.5;
  lists_prime = am_choose_hash_prime ((x <= LISTS_PRIME ? LISTS_PRIME : x));
  List = malloc (lists_prime * sizeof (void *));
  memset (List, 0, lists_prime * sizeof (void *));
  max_lists = 0.7 * lists_prime;
}