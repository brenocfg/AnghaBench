#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_run (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  devptsfs ; 
 int /*<<< orphan*/  do_mount (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  procfs ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__) ; 
 char* strerror (int) ; 
 scalar_t__ strlen (char*) ; 
 int xX_main_Xx (int,char* const*,char*) ; 

int main(int argc, char *const argv[]) {
    char envp[100] = {0};
    if (getenv("TERM"))
        strcpy(envp, getenv("TERM") - strlen("TERM") - 1);
    int err = xX_main_Xx(argc, argv, envp);
    if (err < 0) {
        fprintf(stderr, "%s\n", strerror(-err));
        return err;
    }
    do_mount(&procfs, "proc", "/proc", 0);
    do_mount(&devptsfs, "devpts", "/dev/pts", 0);
    cpu_run(&current->cpu);
}