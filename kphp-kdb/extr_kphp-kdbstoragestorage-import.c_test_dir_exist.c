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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int PATH_BUFFSIZE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,char const* const) ; 
 scalar_t__ stat (char const* const,struct stat*) ; 
 int strlen (char const* const) ; 

__attribute__((used)) static void test_dir_exist (const char *const path) {
  if (strlen (path) > (PATH_BUFFSIZE - 256)) {
    kprintf ("%s too long\n", path);
    exit (1);
  }
  struct stat buf;
  if (stat (path, &buf) || !S_ISDIR (buf.st_mode)) {
    kprintf ("Directory %s doesn't exist\n", path);
    exit (1);
  }
}