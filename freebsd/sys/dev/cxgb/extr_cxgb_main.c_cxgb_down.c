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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  t3_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t3_sge_stop (struct adapter*) ; 

__attribute__((used)) static void
cxgb_down(struct adapter *sc)
{
	t3_sge_stop(sc);
	t3_intr_disable(sc);
}