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
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int rename (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int verbosity ; 

int rename_temporary_snapshot (const char *name) {
  int l = strlen (name);
  assert (l >= 4 && !strcmp (name + l - 4, ".tmp") && l <= 256);
  static char tmpbuff[256];
  memcpy (tmpbuff, name, l - 4);
  tmpbuff[l - 4] = 0;
  if (verbosity > 1) {
    fprintf (stderr, "renaming temporary snapshot %s to %s\n", name, tmpbuff);
  }
  if (!access (tmpbuff, 0)) {
    fprintf (stderr, "fatal: snapshot %s already exists\n", tmpbuff);
    return -1;
  }
  return rename (name, tmpbuff);
}