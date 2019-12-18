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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  cin ; 
 int code ; 
 int empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lostpeer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
reset(int argc, char *argv[])
{
	int nfnd = 1;

	if (argc == 0 && argv != NULL) {
		UPRINTF("usage: %s\n", argv[0]);
		code = -1;
		return;
	}
	while (nfnd > 0) {
		if ((nfnd = empty(cin, NULL, 0)) < 0) {
			warn("Error resetting connection");
			code = -1;
			lostpeer(0);
		} else if (nfnd)
			(void)getreply(0);
	}
}