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
 int /*<<< orphan*/  IB_CPI_BASEVER_F ; 
 scalar_t__ IB_CPI_TRAP_QKEY_F ; 
 int /*<<< orphan*/  _dump_fields (char*,int,void*,int /*<<< orphan*/ ,scalar_t__) ; 

void mad_dump_classportinfo(char *buf, int bufsz, void *val, int valsz)
{
	/* no FIRST_F and LAST_F for CPI field enums, must do a hack */
	_dump_fields(buf, bufsz, val, IB_CPI_BASEVER_F, IB_CPI_TRAP_QKEY_F + 1);
}