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
typedef  char const* uint32_t ;
struct buf_pr {int dummy; } ;

/* Variables and functions */
 char const* IP_FW_TARG ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,...) ; 

void
bprint_uint_arg(struct buf_pr *bp, const char *str, uint32_t arg)
{

	if (str != NULL)
		bprintf(bp, "%s", str);
	if (arg == IP_FW_TARG)
		bprintf(bp, "tablearg");
	else
		bprintf(bp, "%u", arg);
}