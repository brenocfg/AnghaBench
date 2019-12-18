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

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  msglog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usage()
{
	msglog(LOG_NOTICE,
	       "uid %u: usage: vacation [-a alias] [-C cfpath] [-d] [-f db] [-i] [-j] [-l] [-m msg] [-R returnaddr] [-r interval] [-s sender] [-t time] [-U] [-x] [-z] login\n",
	       getuid());
	exit(EX_USAGE);
}