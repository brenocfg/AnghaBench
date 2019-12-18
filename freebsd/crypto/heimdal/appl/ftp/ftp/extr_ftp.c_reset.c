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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cin ; 
 int code ; 
 int empty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lostpeer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
reset (int argc, char **argv)
{
    fd_set mask;
    int nfnd = 1;

    FD_ZERO (&mask);
    while (nfnd > 0) {
	if (fileno (cin) >= FD_SETSIZE)
	    errx (1, "fd too large");
	FD_SET (fileno (cin), &mask);
	if ((nfnd = empty (&mask, 0)) < 0) {
	    warn ("reset");
	    code = -1;
	    lostpeer(0);
	} else if (nfnd) {
	    getreply(0);
	}
    }
}