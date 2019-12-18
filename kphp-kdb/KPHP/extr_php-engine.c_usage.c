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
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  usage_default_desc () ; 
 int /*<<< orphan*/  usage_default_info () ; 
 int /*<<< orphan*/  usage_default_params () ; 
 int /*<<< orphan*/  usage_desc () ; 
 int /*<<< orphan*/  usage_params () ; 

void usage (void) {
  printf ("usage: %s ", progname);

  usage_default_params();
  printf (" ");
  usage_params();

  printf ("\n");

  usage_default_info();

  usage_default_desc();
  usage_desc();

  exit (2);
}