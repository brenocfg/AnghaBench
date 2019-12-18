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
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_application(const char *command) {
    printf("executing: %s\n", command);
    if (fork() == 0) {
        /* Child process */
        setsid();
        if (fork() == 0) {
            /* This is the child */
            execl(_PATH_BSHELL, _PATH_BSHELL, "-c", command, NULL);
            /* not reached */
        }
        exit(0);
    }
    wait(0);
}