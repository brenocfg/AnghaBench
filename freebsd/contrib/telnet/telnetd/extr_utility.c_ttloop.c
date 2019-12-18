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
 int /*<<< orphan*/  DIAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  TD_REPORT ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ nbackp ; 
 scalar_t__ ncc ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  netibuf ; 
 int /*<<< orphan*/  netip ; 
 scalar_t__ nfrontp ; 
 int /*<<< orphan*/  output_data (char*,...) ; 
 int /*<<< orphan*/  pbackp ; 
 int /*<<< orphan*/  pfrontp ; 
 int /*<<< orphan*/  ptyobuf ; 
 scalar_t__ read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  telrcv () ; 

void
ttloop()
{

    DIAG(TD_REPORT, output_data("td: ttloop\r\n"));
    if (nfrontp - nbackp > 0) {
	netflush();
    }
    ncc = read(net, netibuf, sizeof netibuf);
    if (ncc < 0) {
	syslog(LOG_INFO, "ttloop:  read: %m");
	exit(1);
    } else if (ncc == 0) {
	syslog(LOG_INFO, "ttloop:  peer died: %m");
	exit(1);
    }
    DIAG(TD_REPORT, output_data("td: ttloop read %d chars\r\n", ncc));
    netip = netibuf;
    telrcv();			/* state machine */
    if (ncc > 0) {
	pfrontp = pbackp = ptyobuf;
	telrcv();
    }
}