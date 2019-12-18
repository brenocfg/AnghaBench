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
struct TYPE_3__ {scalar_t__ mul1; scalar_t__ mul0; scalar_t__ d; int /*<<< orphan*/ * sums; int /*<<< orphan*/ * used; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ perfect_hash ;

/* Variables and functions */
 int /*<<< orphan*/  init_bits_cnt_table () ; 

void ph_init (perfect_hash *h) {
  init_bits_cnt_table();
  h->code = NULL;
  h->used = NULL;
  h->sums = NULL;
  h->d = 0;
  h->mul0 = 0;
  h->mul1 = 0;
}