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
typedef  int u64 ;

/* Variables and functions */
 int EV6__I_STAT__ERRMASK ; 
 int EV6__I_STAT__PAR ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ev6_parse_ibox(u64 i_stat, int print)
{
	int status = MCHK_DISPOSITION_REPORT;

#define EV6__I_STAT__PAR	(1UL << 29)
#define EV6__I_STAT__ERRMASK	(EV6__I_STAT__PAR)

	if (!(i_stat & EV6__I_STAT__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

	if (!print)
		return status;

	if (i_stat & EV6__I_STAT__PAR)
		printk("%s    Icache parity error\n", err_print_prefix);

	return status;
}