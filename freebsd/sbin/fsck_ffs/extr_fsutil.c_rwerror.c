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
typedef  scalar_t__ ufs2_daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIT ; 
 scalar_t__ bkgrdcheck ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfatal (char*,char const*,long) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ reply (char*) ; 

void
rwerror(const char *mesg, ufs2_daddr_t blk)
{

	if (bkgrdcheck)
		exit(EEXIT);
	if (preen == 0)
		printf("\n");
	pfatal("CANNOT %s: %ld", mesg, (long)blk);
	if (reply("CONTINUE") == 0)
		exit(EEXIT);
}