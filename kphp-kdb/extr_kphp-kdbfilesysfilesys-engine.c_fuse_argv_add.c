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
 scalar_t__ MAX_FUSE_PARAMS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fuse_argc ; 
 char** fuse_argv ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void fuse_argv_add (char *s) {
  char *p;
  for (p = strtok (s, "\t "); p != NULL; p = strtok (NULL, "\t ")) {
    assert (fuse_argc < MAX_FUSE_PARAMS);
    fuse_argv[fuse_argc++] = p;
  }
}