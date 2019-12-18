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
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int /*<<< orphan*/  posix_spawn_file_actions_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int do_posix_spawn (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char* const*,char* const*,int /*<<< orphan*/ ) ; 

int
posix_spawn(pid_t *pid, const char *path,
    const posix_spawn_file_actions_t *fa,
    const posix_spawnattr_t *sa,
    char * const argv[], char * const envp[])
{
	return do_posix_spawn(pid, path, fa, sa, argv, envp, 0);
}