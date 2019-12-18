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
struct config_file {scalar_t__* chrootdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__ strncmp (char*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
dnsc_chroot_path(struct config_file *cfg, char *path)
{
    char *nm;
    nm = path;
    if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(nm,
        cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
        nm += strlen(cfg->chrootdir);
    return nm;
}