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
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ lstat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/ * source_dirname ; 

__attribute__((used)) static int check_source_dirname (void) {
  if (source_dirname == NULL) {
    return -1;
  }
  struct stat st;
  if (lstat (source_dirname, &st) < 0) {
    kprintf ("lstat for path '%s' failed. %m\n", source_dirname);
    return -1;
  }
  if (!S_ISDIR (st.st_mode)) {
    kprintf ("'%s' isn't directory.\n", source_dirname);
    return -1;
  }
  return 0;
}