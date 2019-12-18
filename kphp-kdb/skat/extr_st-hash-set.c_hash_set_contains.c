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
typedef  int /*<<< orphan*/  hash_t ;
typedef  int /*<<< orphan*/  hash_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int list_hash_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool hash_set_contains (hash_set_t h, hash_t x) {
  return list_hash_contains (LIST (h, x), x);
}