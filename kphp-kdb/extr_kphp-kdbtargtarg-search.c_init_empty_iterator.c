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
typedef  TYPE_1__* iterator_t ;
struct TYPE_3__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  jump_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFTY ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 

void init_empty_iterator (iterator_t I) {
  I->jump_to = empty_iterator_jump_to;
  I->pos = INFTY;
}