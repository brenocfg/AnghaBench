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
 scalar_t__ strcmp (char*,char*) ; 

int have_flag(int argc, char** argv, char *flag) {
    char** argm = argv + argc;
    argv++;
    if (argv == argm) {
        return 1;
    }
    while (argv != NULL && argv != argm) {
        if (strcmp(*argv, flag) == 0) {
            return 1;
        }
        argv++;
    }
    return 0;
}