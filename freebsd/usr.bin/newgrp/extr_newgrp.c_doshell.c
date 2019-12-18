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
struct TYPE_2__ {char* pw_shell; } ;

/* Variables and functions */
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  execl (char const*,char const*,char*) ; 
 TYPE_1__* pwd ; 

__attribute__((used)) static void
doshell(void)
{
	const char *shell;

	shell = pwd->pw_shell;
	if (*shell == '\0')
		shell = _PATH_BSHELL;
	execl(shell, shell, (char *)NULL);
	err(1, "%s", shell);
}