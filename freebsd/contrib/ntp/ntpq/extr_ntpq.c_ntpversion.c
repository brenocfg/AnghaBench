#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
struct TYPE_2__ {scalar_t__ uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NTP_OLDVERSION ; 
 scalar_t__ NTP_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int pktversion ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
ntpversion(
	struct parse *pcmd,
	FILE *fp
	)
{
	if (pcmd->nargs == 0) {
		(void) fprintf(fp,
			       "NTP version being claimed is %d\n", pktversion);
	} else {
		if (pcmd->argval[0].uval < NTP_OLDVERSION
		    || pcmd->argval[0].uval > NTP_VERSION) {
			(void) fprintf(stderr, "versions %d to %d, please\n",
				       NTP_OLDVERSION, NTP_VERSION);
		} else {
			pktversion = (u_char) pcmd->argval[0].uval;
		}
	}
}