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
struct pt_unit {int last_sense; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ATAPI_REQ_SENSE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char,char,char) ; 
 int pt_command (struct pt_unit*,char*,int,char*) ; 
 int /*<<< orphan*/  pt_completion (struct pt_unit*,char*,char*) ; 

__attribute__((used)) static void pt_req_sense(struct pt_unit *tape, int quiet)
{
	char rs_cmd[12] = { ATAPI_REQ_SENSE, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 };
	char buf[16];
	int r;

	r = pt_command(tape, rs_cmd, 16, "Request sense");
	mdelay(1);
	if (!r)
		pt_completion(tape, buf, "Request sense");

	tape->last_sense = -1;
	if (!r) {
		if (!quiet)
			printk("%s: Sense key: %x, ASC: %x, ASQ: %x\n",
			       tape->name, buf[2] & 0xf, buf[12], buf[13]);
		tape->last_sense = (buf[2] & 0xf) | ((buf[12] & 0xff) << 8)
		    | ((buf[13] & 0xff) << 16);
	}
}