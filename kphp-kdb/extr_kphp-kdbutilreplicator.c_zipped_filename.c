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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

int zipped_filename (const char *filename) {
  const int l = strlen (filename);
  if (l > 7 && !strcmp (filename + l - 7, ".bin.bz")) {
    return 1;
  }
  if (l > 4 && !strcmp (filename + l - 4, ".bin")) {
    return 0;
  }
  return -1;
}