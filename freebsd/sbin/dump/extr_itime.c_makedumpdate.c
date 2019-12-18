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
struct dumpdates {int /*<<< orphan*/  dd_ddate; int /*<<< orphan*/  dd_level; int /*<<< orphan*/  dd_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMPINFMT ; 
 int /*<<< orphan*/  sscanf (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  unctime (char*) ; 

__attribute__((used)) static int
makedumpdate(struct dumpdates *ddp, const char *tbuf)
{
	char un_buf[128];

	(void) sscanf(tbuf, DUMPINFMT, ddp->dd_name, &ddp->dd_level, un_buf);
	ddp->dd_ddate = unctime(un_buf);
	if (ddp->dd_ddate < 0)
		return(-1);
	return(0);
}