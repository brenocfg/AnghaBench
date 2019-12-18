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
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int append_path (char *s, int l, const char *filename) {
  int o = PATH_MAX - l;
  assert (o > 0);
  int r = snprintf (s + l, o, "/%s", filename);
  if (r >= o - 1) {
    kprintf ("append_path fail (buffer overflow)\n");
    exit (1);
  }
  return l + r;
}