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
 int EX_CONFIG ; 
 char** build_server_starter_argv (char const*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_using_server_starter(const char *h2o_cmd, const char *config_file)
{
    char **args = build_server_starter_argv(h2o_cmd, config_file);
    setenv("H2O_VIA_MASTER", "", 1);
    execvp(args[0], args);
    fprintf(stderr, "failed to spawn %s:%s\n", args[0], strerror(errno));
    return EX_CONFIG;
}