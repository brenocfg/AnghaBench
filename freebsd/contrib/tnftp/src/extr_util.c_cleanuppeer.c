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
 int anonftp ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/ * cout ; 
 int data ; 
 scalar_t__ epsv4bad ; 
 scalar_t__ epsv6bad ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ macnum ; 
 int /*<<< orphan*/  proxy ; 
 scalar_t__ unix_proxy ; 
 scalar_t__ unix_server ; 
 int /*<<< orphan*/ * username ; 

void
cleanuppeer(void)
{

	if (cout)
		(void)fclose(cout);
	cout = NULL;
	connected = 0;
	unix_server = 0;
	unix_proxy = 0;
			/*
			 * determine if anonftp was specifically set with -a
			 * (1), or implicitly set by auto_fetch() (2). in the
			 * latter case, disable after the current xfer
			 */
	if (anonftp == 2)
		anonftp = 0;
	data = -1;
	epsv4bad = 0;
	epsv6bad = 0;
	if (username)
		free(username);
	username = NULL;
	if (!proxy)
		macnum = 0;
}