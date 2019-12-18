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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_inv ; 
 int /*<<< orphan*/  sub_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inv_sub_block(uint32_t state[4])
{
  state[0] = sub_word(state[0], S_inv);
  state[1] = sub_word(state[1], S_inv);
  state[2] = sub_word(state[2], S_inv);
  state[3] = sub_word(state[3], S_inv);
}