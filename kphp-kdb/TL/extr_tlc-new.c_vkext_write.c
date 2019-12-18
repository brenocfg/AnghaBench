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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  write_types (int) ; 

int vkext_write (const char *filename) {
  int f = open (filename, O_CREAT | O_WRONLY | O_TRUNC, 0640);
  assert (f >= 0);
  write_types (f);
  close (f);
  return 0;
}