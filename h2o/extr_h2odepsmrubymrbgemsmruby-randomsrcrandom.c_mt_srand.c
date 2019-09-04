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
typedef  int /*<<< orphan*/  mt_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_random_init_genrand (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mt_srand(mt_state *t, unsigned long seed)
{
  mrb_random_init_genrand(t, seed);
}