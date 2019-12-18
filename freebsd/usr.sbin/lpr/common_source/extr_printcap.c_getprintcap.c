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
 int cgetent (char**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getprintcap_int (char*,struct printer*) ; 
 int /*<<< orphan*/  printcapdb ; 

int
getprintcap(const char *printer, struct printer *pp)
{
	int status;
	char *bp;

	if ((status = cgetent(&bp, printcapdb, printer)) < 0)
		return status;
	status = getprintcap_int(bp, pp);
	free(bp);
	return status;
}