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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int /*<<< orphan*/ * log_file ; 

int logfile (char *s) {
  if (log_file) {
    fclose (log_file);
    log_file = NULL;
  }
  log_file = fopen (s, "w");
  if (log_file == NULL) {
    kprintf ("fopen (\"%s\", \"w\") fail. %m\n", s);
  }
  return 0;
}