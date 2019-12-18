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
typedef  int /*<<< orphan*/  tbuf ;
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  nbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EVNT_KERN ; 
 int /*<<< orphan*/  STA_FMT ; 
 int /*<<< orphan*/  report_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintb (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
sync_status(const char *what, int ostatus, int nstatus)
{
	char obuf[256], nbuf[256], tbuf[1024];
#if defined(USE_SNPRINTB) && defined (STA_FMT)
	snprintb(obuf, sizeof(obuf), STA_FMT, ostatus);
	snprintb(nbuf, sizeof(nbuf), STA_FMT, nstatus);
#else
	snprintf(obuf, sizeof(obuf), "%04x", ostatus);
	snprintf(nbuf, sizeof(nbuf), "%04x", nstatus);
#endif
	snprintf(tbuf, sizeof(tbuf), "%s status: %s -> %s", what, obuf, nbuf);
	report_event(EVNT_KERN, NULL, tbuf);
}