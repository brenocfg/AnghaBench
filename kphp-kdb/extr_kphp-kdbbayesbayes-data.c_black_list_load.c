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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  black_list_set (char*,int) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

void black_list_load (int size) {
  static char buff[1 << 20];
  assert (size < (1 << 20));

  int r = read (fd[0], buff, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position ???: %m\n", r, size);
    assert (r == size);
  }

  black_list_set (buff, size - 1);
}