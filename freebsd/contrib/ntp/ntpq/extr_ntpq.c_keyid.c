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
typedef  int /*<<< orphan*/  u_long ;
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
struct TYPE_2__ {scalar_t__ uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NTP_MAXKEY ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ info_auth_keyid ; 

__attribute__((used)) static void
keyid(
	struct parse *pcmd,
	FILE *fp
	)
{
	if (pcmd->nargs == 0) {
		if (info_auth_keyid == 0)
		    (void) fprintf(fp, "no keyid defined\n");
		else
		    (void) fprintf(fp, "keyid is %lu\n", (u_long)info_auth_keyid);
	} else {
		/* allow zero so that keyid can be cleared. */
		if(pcmd->argval[0].uval > NTP_MAXKEY)
		    (void) fprintf(fp, "Invalid key identifier\n");
		info_auth_keyid = pcmd->argval[0].uval;
	}
}