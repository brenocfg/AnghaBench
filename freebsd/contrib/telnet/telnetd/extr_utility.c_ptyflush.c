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
 int /*<<< orphan*/  DIAG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int TD_PTYDATA ; 
 int TD_REPORT ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  output_data (char*,int) ; 
 scalar_t__ pbackp ; 
 scalar_t__ pfrontp ; 
 int /*<<< orphan*/  printdata (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  pty ; 
 scalar_t__ ptyobuf ; 
 int write (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
ptyflush(void)
{
	int n;

	if ((n = pfrontp - pbackp) > 0) {
		DIAG(TD_REPORT | TD_PTYDATA,
		    output_data("td: ptyflush %d chars\r\n", n));
		DIAG(TD_PTYDATA, printdata("pd", pbackp, n));
		n = write(pty, pbackp, n);
	}
	if (n < 0) {
		if (errno == EWOULDBLOCK || errno == EINTR)
			return;
		cleanup(0);
	}
	pbackp += n;
	if (pbackp == pfrontp)
		pbackp = pfrontp = ptyobuf;
}