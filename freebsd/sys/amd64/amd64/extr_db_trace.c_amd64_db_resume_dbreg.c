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
struct dbreg {int dummy; } ;

/* Variables and functions */
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PC_DBREG_CMD_LOAD 128 
 int /*<<< orphan*/  PC_DBREG_CMD_NONE ; 
 int /*<<< orphan*/  dbreg ; 
 int /*<<< orphan*/  dbreg_cmd ; 
 int /*<<< orphan*/  set_dbregs (int /*<<< orphan*/ *,struct dbreg*) ; 

void
amd64_db_resume_dbreg(void)
{
	struct dbreg *d;

	switch (PCPU_GET(dbreg_cmd)) {
	case PC_DBREG_CMD_LOAD:
		d = (struct dbreg *)PCPU_PTR(dbreg);
		set_dbregs(NULL, d);
		PCPU_SET(dbreg_cmd, PC_DBREG_CMD_NONE);
		break;
	}
}