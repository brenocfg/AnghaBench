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
struct sort_entry {int index; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int jv_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sort_cmp(const void* pa, const void* pb) {
  const struct sort_entry* a = pa;
  const struct sort_entry* b = pb;
  int r = jv_cmp(jv_copy(a->key), jv_copy(b->key));
  // comparing by index if r == 0 makes the sort stable
  return r ? r : (a->index - b->index);
}