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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 

void usage (void) {
  printf ("usage: %s [-v] [-V<volume_id>] [-m<split_rem,split_modulo> [-u<username>] [-S] [-p<prefix>] [-g<group_base_path:group_aux_path>] [-L] [-P<dump-file>] user_base_path1:user_aux_path1 ... user_base_pathK:user_aux_pathK\n"
	  "\t\t\tit is possible to give up to 3 aux paths\n"
    "\t-v\toutput statistical and debug information into stderr\n"
	  "\t-p<prefix>\toutput <prefix> before image dumping info\n"
    "\t[-g<group_base_path:group_aux_path>]\timport group images\n"
    "\t-L\tdump import log to stderr\n"
    "\t-T\tdon't write lev_start to the stdout\n"
    "\t-S\ttry to use old secret (by default secrets xored with md5)\n"
    "\t-P<dump-file>\tdumps import log into tab separated format file which could be tranformed with pmemcached-import-dump into pmemcache binlog\n"
    "\t\t\tfirst column old image url, second column new image url\n",
	  progname);
  exit(2);
}