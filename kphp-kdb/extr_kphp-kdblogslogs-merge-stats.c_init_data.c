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
 int engineF ; 
 int engineN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ ** f ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  left_files ; 
 int snprintf (char*,int,char*,char*,int) ; 
 char* stat_name ; 
 int /*<<< orphan*/  stderr ; 

void init_data (void) {
  char fname[100];
  int i;

  for (i = engineF; i < engineN; i++) {
    if (snprintf (fname, 100, "%s%03d", stat_name, i) >= 100) {
      fprintf (stderr, "Filename is too long.\n");
      exit (1);
    }
    f[i] = fopen (fname, "r");
    if (f[i] == NULL) {
      fprintf (stderr, "File '%s' not found.\n", fname);
      exit (1);
    }
    left_files++;
  }
}