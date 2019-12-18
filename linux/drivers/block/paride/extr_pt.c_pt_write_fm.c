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
struct pt_unit {int dummy; } ;

/* Variables and functions */
 int ATAPI_WFM ; 
 int /*<<< orphan*/  PT_TMO ; 
 int /*<<< orphan*/  pt_media_access_cmd (struct pt_unit*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void pt_write_fm(struct pt_unit *tape)
{
	char wm_cmd[12] = { ATAPI_WFM, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };

	pt_media_access_cmd(tape, PT_TMO, wm_cmd, "write filemark");
}