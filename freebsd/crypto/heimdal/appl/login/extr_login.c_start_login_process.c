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
 int /*<<< orphan*/  env ; 
 char* login_conf_get_string (char*) ; 
 int simple_execle (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
start_login_process(void)
{
    char *prog, *argv0;
    prog = login_conf_get_string("login_program");
    if(prog == NULL)
	return 0;
    argv0 = strrchr(prog, '/');

    if(argv0)
	argv0++;
    else
	argv0 = prog;

    return simple_execle(prog, argv0, NULL, env);
}