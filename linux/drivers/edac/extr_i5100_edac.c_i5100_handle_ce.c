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
struct mem_ctl_info {int dummy; } ;
typedef  int /*<<< orphan*/  detail ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,unsigned int,int,char const*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void i5100_handle_ce(struct mem_ctl_info *mci,
			    int chan,
			    unsigned bank,
			    unsigned rank,
			    unsigned long syndrome,
			    unsigned cas,
			    unsigned ras,
			    const char *msg)
{
	char detail[80];

	/* Form out message */
	snprintf(detail, sizeof(detail),
		 "bank %u, cas %u, ras %u\n",
		 bank, cas, ras);

	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     0, 0, syndrome,
			     chan, rank, -1,
			     msg, detail);
}