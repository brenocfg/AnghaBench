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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EX_USAGE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

int
usage(bool explicit)
{
	FILE *fp;

	fp =  explicit ? stdout : stderr;
	fprintf(fp, "%s",
	    "usage:\tbectl {-h | -? | subcommand [args...]}\n"
#if SOON
	    "\tbectl add (path)*\n"
#endif
	    "\tbectl activate [-t] beName\n"
	    "\tbectl check\n"
	    "\tbectl create [-r] [-e {nonActiveBe | beName@snapshot}] beName\n"
	    "\tbectl create [-r] beName@snapshot\n"
	    "\tbectl destroy [-F] {beName | beName@snapshot}\n"
	    "\tbectl export sourceBe\n"
	    "\tbectl import targetBe\n"
	    "\tbectl jail {-b | -U} [{-o key=value | -u key}]... "
	    "{jailID | jailName}\n"
	    "\t      bootenv [utility [argument ...]]\n"
	    "\tbectl list [-DHas] [{-c property | -C property}]\n"
	    "\tbectl mount beName [mountpoint]\n"
	    "\tbectl rename origBeName newBeName\n"
	    "\tbectl {ujail | unjail} {jailID | jailName} bootenv\n"
	    "\tbectl {umount | unmount} [-f] beName\n");

	return (explicit ? 0 : EX_USAGE);
}