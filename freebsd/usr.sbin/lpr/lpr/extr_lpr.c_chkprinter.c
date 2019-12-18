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
#define  PCAPERR_NOTFOUND 131 
#define  PCAPERR_OSERR 130 
#define  PCAPERR_TCLOOP 129 
#define  PCAPERR_TCOPEN 128 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int getprintcap (char const*,struct printer*) ; 
 int /*<<< orphan*/  init_printer (struct printer*) ; 
 int /*<<< orphan*/  pcaperr (int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
chkprinter(const char *ptrname, struct printer *pp)
{
	int status;

	init_printer(pp);
	status = getprintcap(ptrname, pp);
	switch(status) {
	case PCAPERR_OSERR:
	case PCAPERR_TCLOOP:
		errx(1, "%s: %s", ptrname, pcaperr(status));
	case PCAPERR_NOTFOUND:
		errx(1, "%s: unknown printer", ptrname);
	case PCAPERR_TCOPEN:
		warnx("%s: unresolved tc= reference(s)", ptrname);
	}
}