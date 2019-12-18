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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ info_auth_keyid ; 
 int keyid_entered ; 

__attribute__((used)) static void
keyid(
	struct parse *pcmd,
	FILE *fp
	)
{
	if (pcmd->nargs == 0) {
		if (info_auth_keyid == 0 && !keyid_entered)
		    (void) fprintf(fp, "no keyid defined\n");
		else if (info_auth_keyid == 0 && keyid_entered)
		    (void) fprintf(fp, "no keyid will be sent\n");
		else
		    (void) fprintf(fp, "keyid is %lu\n", (u_long)info_auth_keyid);
	} else {
		info_auth_keyid = pcmd->argval[0].uval;
		keyid_entered = 1;
	}
}