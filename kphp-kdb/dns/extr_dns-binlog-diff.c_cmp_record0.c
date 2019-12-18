#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ qtype; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ record_t ;

/* Variables and functions */
 int cmp_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cmp_record0 (record_t *a, record_t *b) {
  const int c = cmp_str (a->name, a->name_len, b->name, b->name_len);
  if (c) { return c; }
  if (a->qtype < b->qtype) { return -1; }
  if (a->qtype > b->qtype) { return  1; }
  return 0;
}