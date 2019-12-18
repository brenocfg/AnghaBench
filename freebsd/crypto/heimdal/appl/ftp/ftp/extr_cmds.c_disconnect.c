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
 int /*<<< orphan*/  command (char*) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/ * cout ; 
 int data ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ macnum ; 
 int /*<<< orphan*/  proxy ; 
 int /*<<< orphan*/  sec_end () ; 

void
disconnect(int argc, char **argv)
{

	if (!connected)
		return;
	command("QUIT");
	if (cout) {
		fclose(cout);
	}
	cout = NULL;
	connected = 0;
	sec_end();
	data = -1;
	if (!proxy) {
		macnum = 0;
	}
}