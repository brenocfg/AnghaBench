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
struct printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
#define  PCAPERR_NOTFOUND 130 
#define  PCAPERR_OSERR 129 
#define  PCAPERR_TCLOOP 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (struct printer*,char*) ; 
 int getprintcap (char const*,struct printer*) ; 
 int /*<<< orphan*/  init_printer (struct printer*) ; 
 int /*<<< orphan*/  printjob (struct printer*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

void
startprinting(const char *printer)
{
	struct printer myprinter, *pp = &myprinter;
	int status;

	init_printer(pp);
	status = getprintcap(printer, pp);
	switch(status) {
	case PCAPERR_OSERR:
		syslog(LOG_ERR, "can't open printer description file: %m");
		exit(1);
	case PCAPERR_NOTFOUND:
		syslog(LOG_ERR, "unknown printer: %s", printer);
		exit(1);
	case PCAPERR_TCLOOP:
		fatal(pp, "potential reference loop detected in printcap file");
	default:
		break;
	}
	printjob(pp);
}