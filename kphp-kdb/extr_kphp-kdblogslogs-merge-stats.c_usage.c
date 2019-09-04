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
  printf ("usage: %s [-u] [-o<output_file>] [-F<first_engine_num>][-N<engines_cnt>] <stat_name>\n"
    "Merge engineN binary files \"<stat_name><server_num>\"\n"
    "  server_num is 3 digit number with leading zeros\n"
	  "\t-o\tname of output file\n"
	  "\t-F<first_engine_num>\tnumber of first engine, default 0\n"
	  "\t-N<engines_cnt>\tnumber of last engine plus 1\n",
	  progname);
  exit (2);
}