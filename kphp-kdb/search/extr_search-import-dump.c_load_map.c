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
 int /*<<< orphan*/  MAP_SIZE ; 
 int /*<<< orphan*/  Map ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* groups_fname ; 
 scalar_t__ map_fd ; 
 scalar_t__ map_size ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

void load_map (int force) {
  if (!groups_fname) {
    if (!force) {
      fprintf (stderr, "warning: no map file specified\n");
    } else {
      fprintf (stderr, "fatal: no map file specified\n");
      exit (2);
    }
    return;
  }
  map_fd = open (groups_fname, O_RDONLY);
  if (map_fd < 0) {
    fprintf (stderr, "cannot open map file %s: %m", groups_fname);
    if (force) {
      exit (2);
    }
    return;
  }
  map_size = read (map_fd, Map, MAP_SIZE);
  close (map_fd);
  if (map_size < 0) {
    map_size = 0;
  }
  if (verbosity > 0) {
    fprintf (stderr, "read %d bytes from map file %s\n", map_size, groups_fname);
  }
}