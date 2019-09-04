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
 char* FullVersionStr ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s\n",  FullVersionStr);
  printf ("usage: tlc [-v] [-h] <TL-schema-file> [program-file]\n"
      "\tTL compiler\n"
      "\t-v\toutput statistical and debug information into stderr\n"
      "\t-o<filename>\toutput schema's expressions with magic-numbers to given file\n"
      "\t-E\twhenever is possible output to stdout expressions\n"
      "\t-t\ttest mode - trying to unserialize TLC output\n");
  exit (2);
}