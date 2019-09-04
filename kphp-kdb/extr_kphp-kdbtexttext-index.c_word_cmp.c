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
struct TYPE_4__ {int len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ word_t ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int word_cmp (word_t *a, word_t *b) {
  int al = a->len, bl = b->len;
  int x = memcmp (a->str, b->str, al < bl ? al : bl);
  return x ? x : al - bl;
}