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
 int /*<<< orphan*/  inv_mix_column (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inv_mix_columns(uint32_t state[4])
{
  state[0] = inv_mix_column(state[0]);
  state[1] = inv_mix_column(state[1]);
  state[2] = inv_mix_column(state[2]);
  state[3] = inv_mix_column(state[3]);
}