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
struct stat {int st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int env_verbosity ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getuid () ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
is_there(char *candidate)
{
        struct stat fin;

        /* XXX work around access(2) false positives for superuser */
        if (access(candidate, X_OK) == 0 &&
            stat(candidate, &fin) == 0 &&
            S_ISREG(fin.st_mode) &&
            (getuid() != 0 ||
            (fin.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0)) {
                if (env_verbosity > 1)
			fprintf(stderr, "#env   matched:\t'%s'\n", candidate);
                return (1);
        }
        return (0);
}