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
 int /*<<< orphan*/  FLUSHK () ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close_driver () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void pcap_assert (const char *what, const char *file, unsigned line)
{
  FLUSHK();
  fprintf (stderr, "%s (%u): Assertion \"%s\" failed\n",
           file, line, what);
  close_driver();
  _exit (-1);
}