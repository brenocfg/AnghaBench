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
 int /*<<< orphan*/  mdelay (int) ; 
 int pt_command (struct pt_unit*,char*,int,char*) ; 
 int pt_completion (struct pt_unit*,char*,char*) ; 
 int /*<<< orphan*/  pt_req_sense (struct pt_unit*,int) ; 

__attribute__((used)) static int pt_atapi(struct pt_unit *tape, char *cmd, int dlen, char *buf, char *fun)
{
	int r;

	r = pt_command(tape, cmd, dlen, fun);
	mdelay(1);
	if (!r)
		r = pt_completion(tape, buf, fun);
	if (r)
		pt_req_sense(tape, !fun);

	return r;
}