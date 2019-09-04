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
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* fd ; 
 char** fnames ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

void fail (void) {
  int i;
  fprintf (stderr, "fatal error, deleting all output files...\n");
  for (i = 2; i <= 4; i++) {
    if (fd[i] >= 0) { close (fd[2]); }
    if (fnames[i]) { 
      fprintf (stderr, "deleting %s\n", fnames[i]); 
      unlink (fnames[i]); 
    }
  }
  exit (2);
}