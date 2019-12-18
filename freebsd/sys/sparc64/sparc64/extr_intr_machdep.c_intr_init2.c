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

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  intr_table_lock ; 
 int /*<<< orphan*/  intrcnt_lock ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

void
intr_init2()
{

	sx_init(&intr_table_lock, "intr sources");
	mtx_init(&intrcnt_lock, "intrcnt", NULL, MTX_SPIN);
}