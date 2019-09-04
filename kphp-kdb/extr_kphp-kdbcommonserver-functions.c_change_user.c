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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 char* DEFAULT_ENGINE_USER ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ getuid () ; 
 scalar_t__ initgroups (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 

int change_user (char *username) {
  struct passwd *pw;
  /* lose root privileges if we have them */
  if (getuid() == 0 || geteuid() == 0) {
    if (username == 0 || *username == '\0') {
      username = DEFAULT_ENGINE_USER;
//      fprintf (stderr, "can't run as root without the -u switch\n");
//      return -1;
    }
    if ((pw = getpwnam (username)) == 0) {
      kprintf ("can't find the user %s to switch to\n", username);
      return -1;
    }
    gid_t gid = pw->pw_gid;
    if (setgroups(1, &gid) < 0) {
      kprintf ("failed to clear supplementary groups list: %m\n");
      return -1;
    }
    if (initgroups(username, gid) != 0) {
      kprintf ("failed to load groups of user %s: %m\n", username);
      return -1;
    }
    if (setgid (pw->pw_gid) < 0 || setuid (pw->pw_uid) < 0) {
      kprintf ("failed to assume identity of user %s\n", username);
      return -1;
    }
  }
  return 0;
}