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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int EX_CONFIG ; 
 int EX_OSERR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ initgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

int main(int argc, char **argv)
{
    struct passwd *user;

    if (argc < 3) {
        fprintf(stderr, "no command (usage: setuidgid user cmd args...)\n");
        return EX_CONFIG;
    }
    --argc;
    ++argv;

    errno = 0;
    if ((user = getpwnam(*argv)) == NULL) {
        if (errno == 0) {
            fprintf(stderr, "unknown user:%s\n", *argv);
            return EX_CONFIG;
        } else {
            perror("getpwnam");
            return EX_OSERR;
        }
    }
    --argc;
    ++argv;

    if (setgid(user->pw_gid) != 0) {
        perror("setgid failed");
        return EX_OSERR;
    }
    if (initgroups(user->pw_name, user->pw_gid) != 0) {
        perror("initgroups failed");
        return EX_OSERR;
    }
    if (setuid(user->pw_uid) != 0) {
        perror("setuid failed");
        return EX_OSERR;
    }

    execvp(*argv, argv);
    fprintf(stderr, "execvp failed to launch file:%s:%s\n", *argv, strerror(errno));
    return EX_OSERR;
}