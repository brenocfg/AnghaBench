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
  printf ("usage: %s [-u] [-i<input_file>] [-o<output_file>] [-U<userN>] [-E<engineN>]\n"
    "Prepares binary files (default \"to<server_num>.tmp\") with friends of friends\n"
    "  server_num is 3 digit number maybe with leading zeros\n"
	  "\t-i\tname of input binary file from\n"
	  "\t-o\tname of output binary file\n"
	  "\t-U\tmaximal expected total number of users\n"
	  "\t-E\tnumber of friend engines\n",
	  progname);
  exit (2);
}