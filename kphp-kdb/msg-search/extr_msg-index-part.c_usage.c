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
  printf ("usage: %s [-v] [-w<modulus>:<remainder>] [-u<users-index-file>] <inbox-fname> <outbox-fname>\n"
	  "\tResulting index file is written to stdout\n"
	  "\t-v\toutput statistical information into stderr\n"
	  "\t-w\tprocess only users with user_id MOD modulus == remainder\n"
	  "\t-u\tload specified users index file for indexing message senders\n",
	  progname);
  exit(2);
}