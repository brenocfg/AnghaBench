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
struct fd {int dummy; } ;

/* Variables and functions */
 int _ENOEXEC ; 
 int elf_exec (struct fd*,char const*,char const*,char const*) ; 

__attribute__((used)) static int format_exec(struct fd *fd, const char *file, const char *argv, const char *envp) {
    int err = elf_exec(fd, file, argv, envp);
    if (err != _ENOEXEC)
        return err;
    // other formats would go here
    return _ENOEXEC;
}