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
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REFID_HASH ; 
 int /*<<< orphan*/  REFID_IPV4 ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drefid ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* showdrefid2str () ; 

__attribute__((used)) static void
showdrefid(
	struct parse *pcmd,
	FILE *fp
	)
{
	if (pcmd->nargs == 0) {
		(void) fprintf(fp, "drefid value is %s\n", showdrefid2str());
		return;
	} else if (STREQ(pcmd->argval[0].string, "hash")) {
		drefid = REFID_HASH;
	} else if (STREQ(pcmd->argval[0].string, "ipv4")) {
		drefid = REFID_IPV4;
	} else {
		(void) fprintf(fp, "What?\n");
		return;
	}
	(void) fprintf(fp, "drefid value set to %s\n", showdrefid2str());
}