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
typedef  int /*<<< orphan*/  filename ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARGV_MAX ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,...) ; 
 int _EFAULT ; 
 int _ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int sys_execve (char*,char*,char*) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 
 int user_read_string_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

dword_t _sys_execve(addr_t filename_addr, addr_t argv_addr, addr_t envp_addr) {
    char filename[MAX_PATH];
    if (user_read_string(filename_addr, filename, sizeof(filename)))
        return _EFAULT;

    int err = _ENOMEM;
    char *argv = malloc(ARGV_MAX);
    if (argv == NULL)
        goto err_free_argv;
    err = user_read_string_array(argv_addr, argv, ARGV_MAX);

    if (err < 0)
        goto err_free_argv;
    char *envp = malloc(ARGV_MAX);
    if (envp == NULL)
        goto err_free_envp;
    err = user_read_string_array(envp_addr, envp, ARGV_MAX);
    if (err < 0)
        goto err_free_envp;

    STRACE("execve(\"%s\", {", filename);
    const char *args = argv;
    while (*args != '\0') {
        STRACE("\"%s\", ", args);
        args += strlen(args) + 1;
    }
    args = envp;
    while (*args != '\0') {
        STRACE("\"%s\", ", args);
        args += strlen(args) + 1;
    }
    STRACE("})");

    return sys_execve(filename, argv, envp);

err_free_envp:
    free(envp);
err_free_argv:
    free(argv);
    return err;
}