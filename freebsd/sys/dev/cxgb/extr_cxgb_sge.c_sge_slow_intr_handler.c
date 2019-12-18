#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slow_intr_mask; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INT_ENABLE0 ; 
 int /*<<< orphan*/  t3_read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_slow_intr_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sge_slow_intr_handler(void *arg, int ncount)
{
	adapter_t *sc = arg;

	t3_slow_intr_handler(sc);
	t3_write_reg(sc, A_PL_INT_ENABLE0, sc->slow_intr_mask);
	(void) t3_read_reg(sc, A_PL_INT_ENABLE0);
}