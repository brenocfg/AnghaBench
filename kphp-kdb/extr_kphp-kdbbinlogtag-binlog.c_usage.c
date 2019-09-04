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
  printf ("%s\n", FullVersionStr);
  printf (
    "tag-binlog [-u<username>] [-v] <binlog>\n"
    "\tAppending LEV_TAG tool.\n"
    "\t[-v]\t\toutput statistical and debug information into stderr\n"
    "\t[-a]\t\tappend random tag\n"
    "\t[-t<tag>]\tappend given tag\n"
    "\t[-i]\t\tinformation mode - print tag and exit\n"
  );
  exit (2);
}