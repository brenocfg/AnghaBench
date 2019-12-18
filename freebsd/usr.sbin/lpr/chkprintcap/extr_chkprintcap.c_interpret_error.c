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
struct printer {int /*<<< orphan*/  printer; } ;

/* Variables and functions */
#define  PCAPERR_OSERR 131 
#define  PCAPERR_SUCCESS 130 
#define  PCAPERR_TCLOOP 129 
#define  PCAPERR_TCOPEN 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  problems ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
interpret_error(const struct printer *pp, int error)
{
	switch(error) {
	case PCAPERR_OSERR:
		err(++problems, "reading printer database");
	case PCAPERR_TCLOOP:
		++problems;
		warnx("%s: loop detected in tc= expansion", pp->printer);
		return 1;
	case PCAPERR_TCOPEN:
		warnx("%s: unresolved tc= expansion", pp->printer);
		return 1;
	case PCAPERR_SUCCESS:
		break;
	default:
		errx(++problems, "unknown printcap library error %d", error);
	}
	return 0;
}