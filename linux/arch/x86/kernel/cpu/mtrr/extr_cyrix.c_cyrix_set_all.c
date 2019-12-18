#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ CX86_CCR0 ; 
 scalar_t__ CX86_CCR4 ; 
 TYPE_1__* arr_state ; 
 int /*<<< orphan*/ * ccr_state ; 
 int /*<<< orphan*/  cyrix_set_arr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_set () ; 
 int /*<<< orphan*/  prepare_set () ; 
 int /*<<< orphan*/  setCx86 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyrix_set_all(void)
{
	int i;

	prepare_set();

	/* the CCRs are not contiguous */
	for (i = 0; i < 4; i++)
		setCx86(CX86_CCR0 + i, ccr_state[i]);
	for (; i < 7; i++)
		setCx86(CX86_CCR4 + i, ccr_state[i]);

	for (i = 0; i < 8; i++) {
		cyrix_set_arr(i, arr_state[i].base,
			      arr_state[i].size, arr_state[i].type);
	}

	post_set();
}