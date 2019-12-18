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
typedef  int /*<<< orphan*/  u32 ;
struct sysc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  sysc_write (struct sysc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysc_module_enable_quirk_sgx(struct sysc *ddata)
{
	int offset = 0xff08;	/* OCP_DEBUG_CONFIG */
	u32 val = BIT(31);	/* THALIA_INT_BYPASS */

	sysc_write(ddata, offset, val);
}